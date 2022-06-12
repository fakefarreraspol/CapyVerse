project "Capyverse"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++14"
    staticruntime "on"
    characterset ("MBCS")

    debugdir("$(SolutionDir)/Output")
    targetdir("$(SolutionDir)Build/$(Configuration)")
    objdir("$(SolutionDir)Build/$(Configuration)/Obj/")
    links {
        "Box2D",
        "SDL2",
        "SDL2_ttf",
        "SDL2main",
        "OptickCore",
        "SDL2_mixer",
        "SDL2_image",
        "kernel32",
        "user32",
        "gdi32",
        "winspool",
        "comdlg32",
        "advapi32",
        "shell32",
        "ole32",
        "oleaut32",
        "uuid",
        "odbc32",
        "odbccp32"
    }
    libdirs {
        "$(ProjectDir)Source/External/SDL/libx86",
        "$(ProjectDir)Source/External/SDL_ttf/libx86",
        "$(ProjectDir)Source/External/SDL_image/libx86",
        "$(ProjectDir)Source/External/SDL_mixer/libx86",
    }


    files {
        "Source/*.cpp",
        "Source/*.h",
        "Source/External/PugiXML/src/*.cpp",
        "Source/External/PugiXML/src/*.hpp"
    }
    includedirs {
        "$(ProjectDir)Source/External",
        "$(ProjectDir)Source/External/SDL/include",
        "$(ProjectDir)Source/External/SDL_ttf/include",
        "$(ProjectDir)Source/External/SDL_image/include",
        "$(ProjectDir)Source/External/SDL_mixer/include",
        "$(ProjectDir)Source/External/PugiXml/src",
        "$(ProjectDir)Source/External/Optick/include",
        "$(ProjectDir)Source/External/Box2D/Box2D"
    }
    defines {
        "WINDOWS"
    }

    filter {"configurations:Debug"}
        buildoptions "/MDd"
        runtime "Debug"
        symbols "on"
        libdirs { "$(ProjectDir)Source/External/Optick/lib/debug", "$(ProjectDir)Source/External/Box2D/libx86/Debug"}

    filter {"configurations:Release"}
        buildoptions "/MD"
        runtime "Release"
        optimize "on"
        libdirs { "$(ProjectDir)Source/External/Optick/lib/release", "$(ProjectDir)Source/External/Box2D/libx86/Release"}

    vpaths{
        ["Source/App"] = {"Source/App.h", "Source/App.cpp", "Source/Main.cpp"},

        ["Source/Modules"] = "Source/Module.h",

        ["Source/Modules/Core"] = {"Source/Audio.h", "Source/Audio.cpp", 
                            "Source/Map.h","Source/Map.cpp",
                            "Source/Render.h","Source/Render.cpp",
                            "Source/Window.h","Source/Window.cpp",
                            "Source/Input.h","Source/Input.cpp",
                            "Source/Textures.h","Source/Textures.cpp",
                            "Source/FadeToBlack.h","Source/FadeToBlack.cpp",
                            "Source/Pause.h","Source/Pause.cpp",
                            "Source/StatsMenu.h", "Source/StatsMenu.cpp",
                            "Source/Fonts.h","Source/Fonts.cpp",
                            "Source/Physics.h", "Source/Physics.cpp",
                            "Source/Transitions.h", "Source/Transitions.cpp",
                            "Source/Particles.h", "Source/Particles.cpp"},

        ["Source/Modules/Gameplay/Dialog"] = { "Source/Dialog.h","Source/Dialog.cpp",
                                        "Source/DialogManager.h","Source/DialogManager.cpp",
                                        "Source/DialogNode.h","Source/DialogNode.cpp"},

        ["Source/Modules/Gameplay/Entities"] = {"Source/Entity.h", "Source/EntityManager.h", "Source/EntityManager.cpp"},

        ["Source/Modules/Gameplay/Entities/Capybaras"] = {"Source/Capybara.h", "Source/Capybara.cpp",
                                                    "Source/Chinabara.h", "Source/Chinabara.cpp",
                                                    "Source/Punkibara.h", "Source/Punkibara.cpp",
                                                    "Source/Retrobara.h", "Source/Retrobara.cpp",
                                                    "Source/Simpbara.h", "Source/Simpbara.cpp",
                                                    "Source/Rainbowbara.h", "Source/Rainbowbara.cpp",
                                                    "Source/Emobara.h", "Source/Emobara.cpp",
                                                    "Source/Chadbara.h", "Source/Chadbara.cpp",
                                                    "Source/Egirlbara.h", "Source/Egirlbara.cpp",
                                                    "Source/Pinkbara.h", "Source/Pinkbara.cpp"},

        ["Source/Modules/Gameplay/Entities/Characters"] = {"Source/Player.h", "Source/Player.cpp",
                                                    "Source/NPC.h", "Source/NPC.cpp",
                                                    "Source/Enemy.h", "Source/Enemy.cpp"},

        ["Source/Modules/Gameplay/Entities/Items"] = {"Source/Item.h",
                                                      "Source/Items.h", "Source/Items.cpp",
                                                      "Source/Inventory.h", "Source/Inventory.cpp",
                                                      "Source/ItemHolder.h"},

        ["Source/Modules/Gameplay/Entities/Props"] = {"Source/Lever.h", "Source/Lever.cpp",
                                                     "Source/Bridge.h"},

        ["Source/Modules/Gameplay/Scenes"] = {"Source/Intro.h", "Source/Intro.cpp",
                                              "Source/MainMenu.h", "Source/MainMenu.cpp",
                                              "Source/End.h", "Source/End.cpp",
                                              "Source/Scene.h", "Source/Scene.cpp"},
        
        ["Source/Modules/Gameplay/Scenes/Battle"] = {"Source/BattleManager.h", "Source/BattleManager.cpp",
                                                     "Source/BattleScene1.h", "Source/BattleScene1.cpp",
                                                     "Source/BattleScene2.h", "Source/BattleScene2.cpp",
                                                     "Source/BattleScene3.h", "Source/BattleScene3.cpp",
                                                     "Source/BattleScene4.h", "Source/BattleScene4.cpp",
                                                     "Source/BattleScene5.h", "Source/BattleScene5.cpp",
                                                     "Source/BattleScene6.h", "Source/BattleScene6.cpp",
                                                     "Source/BattleScene7.h", "Source/BattleScene7.cpp",
                                                     "Source/EOBScene.h", "Source/EOBScene.cpp"},

        ["Source/Modules/Gameplay/Quest"] = {"Source/Quest.h", "Source/QuestManager.h", "Source/QuestManager.cpp"},
        
        ["Source/Utils"] = {"Source/Log.h", "Source/Log.cpp",
                            "Source/Animation.h",
                            "Source/DynArray.h",
                            "Source/Defs.h",
                            "Source/SString.h",
                            "Source/Timer.h", "Source/Timer.cpp",
                            "Source/TaskQueue.h", "Source/TaskQueue.cpp",
                            "Source/Point.h",
                            "Source/PerfTimer.h", "Source/PerfTimer.cpp",
                            "Source/List.h",
                            "Source/Collider.h", "Source/Collider.cpp",
                            "Source/Queue.h", "Source/easings.h",
                            "Source/Particle.h", "Source/Particle.cpp"},

        ["Source/UI"] = {"Source/GuiManager.h", "Source/GuiManager.cpp",
                        "Source/GuiBar.h", "Source/GuiBar.cpp",
                        "Source/GuiButton.h", "Source/GuiButton.cpp",
                        "Source/GuiCheckBox.h", "Source/GuiCheckBox.cpp",
                        "Source/GuiControl.h",
                        "Source/GuiSlider.h", "Source/GuiSlider.cpp",
                        "Source/GuiSliderBar.h", "Source/GuiSliderBar.cpp",
                        "Source/GuiText.h", "Source/GuiText.cpp"},
                        
        ["PugiXML"] = {"Source/External/PugiXML/src/*.hpp", "Source/External/PugiXML/src/*.cpp"}
    }