//use cc::Build;
//use glob::glob;
use std::env;
use std::path::PathBuf;
use std::process::Command;

fn main() {
    let msbuild_path = format!("{}\\MSBuild\\Current\\Bin\\MSBuild.exe", vswhere::Config::new().run_default_path().unwrap()[0].installation_path().to_str().unwrap());

    let profile = env::var("PROFILE").unwrap();
    let architecture = env::var("CARGO_CFG_TARGET_ARCH").unwrap();

    let output = Command::new(msbuild_path)
        .arg("..\\Highcall Library.sln")
        .arg(format!("/p:Configuration={}", profile))
        .output();

    if !output.is_ok() {
        return;
    }
    
    println!("cargo:rustc-link-search=../Current/Build/{}/{}", if architecture == "x86_64" {"x64"} else {"x86"}, profile);
    println!("cargo:rustc-link-lib=static=highcall");
    println!("cargo:rustc-link-lib=dylib=user32");
    
    let bindings = bindgen::builder()
        .clang_arg("-Wno-error=invalid-token-paste")
        .header("../Current/Build/Include/highcall.h")
        .whitelist_function("Hc.*")
        .rustfmt_bindings(true)
        .generate()
        .expect("Unable to generate bindings");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        //.write_to_file(out_path.join("bindings.rs"))
        .write_to_file("src/bindings.rs")
        .expect("Couldn't write bindings!");
    
    // Build::new()+
    //     .include("../Current/Build/Include")
    //     .files(glob("../Current/**/*.c").unwrap().map(|f| f.unwrap().into_boxed_path()))
    //     .files(glob("../Current/**/*.asm").unwrap().map(|f| f.unwrap().into_boxed_path()))
    //     .compile("highcall");
    // 
    
}