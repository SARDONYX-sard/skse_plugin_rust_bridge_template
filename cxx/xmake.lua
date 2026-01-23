local PLUGIN_NAME<const> = "MyPlugin"
local AUTHOR_NAME<const> = "Author Name"
local DESCRIPTION<const> = "Plugin Description"

includes("../extern/CommonLibVR_NG")
includes("../rust/bridge")

target(PLUGIN_NAME, function ()
    add_deps("commonlibsse-ng")
    add_deps("rust_bridge")

    add_headerfiles("include/**.hh")
    add_includedirs("include", { public = true })
    set_pcxxheader("include/pch.hh")
    add_files("src/**.cc")

    -- Rust bridge
    add_includedirs("../target/cxxbridge", { public = true })
    add_headerfiles("../target/cxxbridge/**.h")
    add_files("../target/cxxbridge/**.cc")
    add_linkdirs("../target/release")
    add_links("bridge", { public = true })
    -- Rust std deps
    if is_plat("windows") then
        add_links("ntdll", "userenv", "ws2_32", { public = true })
    end
    --

    add_rules("commonlibsse-ng.plugin", {
        name = PLUGIN_NAME,
        author = AUTHOR_NAME,
        description = DESCRIPTION,
    })
end)
