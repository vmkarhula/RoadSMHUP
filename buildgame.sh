g++ \
-std=c++17 \
-Iexternal/include/ \
-Iexternal/include/DearImGUI \
-Iexternal/include/DearImGUI/backends \
ROADSHMUP/ShmupMain.cpp \
ROADSHMUP/ShmupGame.cpp \
ROADSHMUP/OpenGLTexture.cpp \
ROADSHMUP/Shader.cpp \
external/source/glad/glad.c \
external/source/DearImGUI/imgui.cpp \
external/source/DearImGUI/imgui_draw.cpp \
external/source/DearImGUI/imgui_tables.cpp \
external/source/DearImGUI/imgui_widgets.cpp \
external/source/DearImGUI/backends/imgui_impl_glfw.cpp \
external/source/DearImGUI/backends/imgui_impl_opengl3.cpp \
-lGL -lGLU -lglut -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor 