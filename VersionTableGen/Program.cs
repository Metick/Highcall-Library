using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Text.Json;

namespace VersionTableGen
{
    class Program
    {
        static void Main(string[] args)
        {
            using var httpClient = new HttpClient { BaseAddress = new Uri("https://raw.githubusercontent.com/j00ru/windows-syscalls/master/") };
            void GenerateVersionTable(string repoPath, string outputPath) => GenerateVersionTableFromJsonStream(httpClient.GetStreamAsync(repoPath).Result, outputPath);

            GenerateVersionTable("x64/json/nt-per-syscall.json", "version_table_86_64.h");
            GenerateVersionTable("x64/json/win32k-per-syscall.json", "version_table_ntuser_86_64.h");
            GenerateVersionTable("x86/json/nt-per-syscall.json", "version_table_86.h");
            GenerateVersionTable("x86/json/win32k-per-syscall.json", "version_table_ntuser_86.h");

            Console.WriteLine("Done.");
        }

        static void GenerateVersionTableFromJsonStream(Stream stream, string outputFilePath)
        {
            Console.WriteLine($"Generating {outputFilePath}");
            using var jsonDocument = JsonDocument.Parse(stream);
            using var streamWriter = new StreamWriter(outputFilePath, false);
            streamWriter.WriteLine("#pragma once");
            streamWriter.WriteLine(@"#include ""../../public/base.h""");
            GenerateArray(streamWriter, jsonDocument, outputFilePath.EndsWith("64.h"));
            stream.Dispose();
        }

        static void GenerateArray(StreamWriter streamWriter, JsonDocument jsonDocument, bool is64bit)
        {
            foreach (var jsonProperty in jsonDocument.RootElement.EnumerateObject())
            {
                var syscallList = new List<int>();
               
                void AddSyscallsForSystem(string systemName, params string[] versions)
                {
                    // This windows version is not supported at all
                    if (!jsonProperty.Value.TryGetProperty(systemName, out var jsonElement))
                    {
                        syscallList.AddRange(Enumerable.Repeat(-1, versions.Count()));
                        return;
                    }

                    foreach (var version in versions)
                    {
                        // this build is not supported
                        if (!jsonElement.TryGetProperty(version, out var el))
                        {
                            syscallList.Add(-1);
                        }
                        else
                        {
                            syscallList.Add(el.GetInt32());
                        }
                    }
                }

                // could be read from some json or toml to avoid building it again
                // order is important
                AddSyscallsForSystem("Windows 7", "SP0", "SP1");
                AddSyscallsForSystem("Windows 8", "8.0", "8.1");
                AddSyscallsForSystem("Windows 10", "1507", "1511", "1607", "1703", "1709", "1803", "1809", "1903", "1909", "2004", "20H2");

                var syscallName = jsonProperty.Name;
                if (!syscallList.All(s => s == -1))
                {
                    var cArray = $"SYS_INDEX sciTable_{(is64bit ? "86_64" : "86")}_{syscallName}[] = {{{string.Join(", ", syscallList)}}};";
                    streamWriter.WriteLine(cArray);
                }
                //else
                //{
                //    Console.WriteLine($"Skipping {syscallName}");
                //}
            }
        }
    }
}
