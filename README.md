# UntitledVulkanGameEngine
> Last stable release: 0.5.5.1

> Current code version: 0.5.5.2

> Currently stable on: Linux, MacOS, BSD, Windows

> NOTE: The project passes CI checks. Ubuntu 18.4 uses a very old GCC version which makes it fail every time. This should be resolved if Github actions switches to Ubuntu 20

> Development status: Under heavy construction, we commit directly to master so there will be and possibly are countless bugs in the current master branch
## Information
A game engine that is simple to develop for! The UntitledVulkanGameEngine is a fast, 3D game engine written in C++. It uses Vulkan and Modern OpenGL as graphics APIs and has a simple and easy to use C++ scripting API. The engine follows the Gentoo philosophy which means that everything is compiled by the user, no binaries needed. We also support multiple platofrms like Linux, MacOS and BSD. For patchnotes, announcements and development logs join our [discord server](https://discord.gg/4TAwNSx) and subscribe to our [youtube channel](https://www.youtube.com/channel/UCWKEvueStyfeMGnkvVJuGxQ)
## Learning
You can start learning the engine from the source code or you can go to the [wiki](https://github.com/MadLadSquad/UntitledVulkanGameEngine/wiki) where you can go through a tutorial and after that look at the documentation
## Development
Follow [the trello](https://trello.com/b/0upjsxT0/untitledvukangameengine2) for a board detailing which parts of the engine I am currently working on.
Modules development status:
-   OpenGL rendered: Under construction
-   Vulkan renderer: Planning phase
-   Editor: Under construction
-   Native scripting: Under construction
-   Event system: Finished
-   Scene system: Finished
-   Window system: Finished
-   Renderer interface: Finished
-   Input: Finished
-   2D audio: Under construction
-   3D audio: Under construction
-   Renderer manager: Finished
-   API planning and design: Finished
-   Game framework: 50% finished
## Q&A
Q: It's called the UntitledVulkanEngine but where is the Vulkan renderer

A: The vulkan renderer is going to be built in the future because we are first trying to lay out solid foundations so we can add it without serious problems
## Open-source libraries and SDKs we use
-   GLFW - https://github.com/glfw/glfw
-   GLEW - https://github.com/nigels-com/glew
-   GLM - https://github.com/g-truc/glm
-   EnTT - https://github.com/skypjack/entt
-   Dear imgui - https://github.com/ocornut/imgui
-   yaml-cpp - https://github.com/jbeder/yaml-cpp
-   stb_* - https://github.com/nothings/stb
-   VulkanSDK - https://vulkan.lunarg.com/
-   OpenAL - https://www.openal.org/
-   zlib - https://github.com/madler/zlib
