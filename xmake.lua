set_project("xauat-c99-cpp11-guide")
set_version("1.0.0")
set_xmakever("2.9.0")
add_rules("mode.debug", "mode.release")

-- 每个源文件都是独立练习，不能把90个main链接进同一个程序。
for _, language in ipairs({"c", "cpp"}) do
    local extension = language == "c" and ".c" or ".cpp"
    for _, source in ipairs(os.files("src/" .. language .. "/*" .. extension)) do
        local slug = path.basename(source)
        target(language .. "_" .. slug)
            set_kind("binary")
            set_languages(language == "c" and "c99" or "cxx11")
            set_warnings("all", "error")
            if not is_plat("windows") then
                add_cxflags("-Wextra", "-Wpedantic")
            end
            if language == "c" and is_plat("linux", "macosx", "bsd") then
                add_links("m")
            end
            add_files(source)
            set_basename(slug)
            set_targetdir("build/xmake/" .. language)
            set_objectdir("build/xmake/.objs/" .. language .. "/" .. slug)
        target_end()
    end
end

-- 任务回调在xmake运行环境中查找Python，避免依赖某个固定安装路径。
task("check")
    set_menu {usage = "xmake check", description = "Build and verify all C99/C++11 exercises"}
    on_run(function ()
        import("lib.detect.find_tool")
        local python = find_tool("python3") or find_tool("python")
        assert(python, "Python 3 is required")
        os.execv(os.programfile(), {"build", "-y"})
        local environment = {COURSE_BIN = path.join(os.projectdir(), "build/xmake")}
        os.execv(python.program, {"tests/run.py"}, {envs = environment})
        os.execv(python.program, {"tests/labs.py"}, {envs = environment})
        os.execv(python.program, {"tools/check_repo.py"})
    end)
task_end()

task("pdf")
    set_menu {usage = "xmake pdf", description = "Create mobile PDF and PDF with all raw sources"}
    on_run(function ()
        import("lib.detect.find_tool")
        local python = find_tool("python3") or find_tool("python")
        assert(python, "Python 3 is required")
        os.execv(python.program, {"tools/build_pdf.py"})
    end)
task_end()

task("stats")
    set_menu {usage = "xmake stats", description = "Rebuild source frequency tables"}
    on_run(function ()
        import("lib.detect.find_tool")
        local python = find_tool("python3") or find_tool("python")
        assert(python, "Python 3 is required")
        os.execv(python.program, {"tools/analyze_sources.py"})
    end)
task_end()
