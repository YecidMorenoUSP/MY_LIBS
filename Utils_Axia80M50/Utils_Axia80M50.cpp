#include <iostream>

#include "Utils_Axia80M50.h"

#include <imgui.h>
#include <imgui.cpp>
#include <imgui_internal.h>

#include <imgui_draw.cpp>
#include <imgui_widgets.cpp>

#include <imgui_impl_sdl.h>
#include <imgui_impl_sdl.cpp>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_opengl2.cpp>


#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h> 

#include <imgui_plot2.hpp>
#include <imgui_plot2.cpp>




#include <string.h>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	// if ( 2 > argc )
	// {
	// 	fprintf( stderr, "Usage: %s IPADDRESS\n", argv[0] );
	// 	argv[1] = (char *)"192.168.1.1";
	// 	fprintf( stderr,"Conectando a : %s\n",argv[1]);
	// }



	// Axia80M50 * sensor = new Axia80M50((char*)"192.168.1.1");
	// sensor->init();
	// sensor->bias();

	// for(int i = 0 ; i < 500 ; i++){
	// 	sensor->peek();
	// 	sensor->print();
	// }	

	
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
	
	// SDL_Window* window = NULL;
    // SDL_Renderer* renderer = NULL;
	// SDL_CreateWindowAndRenderer(800, 600, window_flags, &window, &renderer);
    SDL_Window* window = SDL_CreateWindow("  ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

	
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }


    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    ImVec4 clear_color = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);

	ImGui::PlotInterface SCOPE;
	SCOPE.y_axis.minimum = -50;
	SCOPE.y_axis.maximum = 50;
	SCOPE.x_axis.minimum = 0;
	SCOPE.x_axis.maximum = 60;
	SCOPE.x_axis.label = std::string("Time [ s ]");
	SCOPE.y_axis.label = std::string("Amplitude [ u ]");
	SCOPE.title = std::string("Axia80M50 Sensor Data");

	std::vector<ImGui::PlotItem> items; 
	ImGui::PlotItem Fx;
	Fx.label = "Fx [ N ] ";
	Fx.type = (ImGui::PlotItem::Type) ImGui::PlotItem::Line; 
	// Fx.color = ImVec4(0.06f, 0.59f, 0.87f, 1.00f);
	Fx.size = 1;
	items.push_back(Fx);

	ImGui::PlotItem Fy;
	Fy.label = "Fy [ N ] ";
	Fy.type = (ImGui::PlotItem::Type) ImGui::PlotItem::Line; 
	// Fy.color = ImVec4(0.06f, 0.59f, 0.87f, 1.00f);
	Fy.size = 1;
	items.push_back(Fy);

	ImGui::PlotItem Fz;
	Fz.label = "Fz [ N ] ";
	Fz.type = (ImGui::PlotItem::Type) ImGui::PlotItem::Line; 
	// Fz.color = ImVec4(0.06f, 0.59f, 0.87f, 1.00f);
	Fz.size = 1;
	items.push_back(Fz);

	ImGui::PlotItem Tx;
	Tx.label = "Tx [ N*m ] ";
	Tx.type = (ImGui::PlotItem::Type) ImGui::PlotItem::Line; 
	// Tx.color = ImVec4(0.06f, 0.59f, 0.87f, 1.00f);
	Tx.size = 1;
	items.push_back(Tx);

	ImGui::PlotItem Ty;
	Ty.label = "Ty [ N*m ] ";
	Ty.type = (ImGui::PlotItem::Type) ImGui::PlotItem::Line; 
	// Ty.color = ImVec4(0.06f, 0.59f, 0.87f, 1.00f);
	Ty.size = 1;
	items.push_back(Ty);

	ImGui::PlotItem Tz;
	Tz.label = "Tz [ N*m ] ";
	Tz.type = (ImGui::PlotItem::Type) ImGui::PlotItem::Line; 
	// Tz.color = ImVec4(0.06f, 0.59f, 0.87f, 1.00f);
	Tz.size = 1;
	items.push_back(Tz);

	std::string LOGS = "Ready...\n";
	

	static bool  sdemo ;
    // Main loop
    bool done = false;
    while (!done)
    {
    
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();



		{
			
			static ImGuiWindowFlags maximized  ;
			static bool showPlot = true;
			static bool close = true;
			static float time = 0;
			
			static bool RUNNING = false;
			static char IP_ [20] = "192.168.1.1";
			static Axia80M50 * sensor = new Axia80M50(IP_);
			
			// ImGui::ShowDemoWindow();
			ImGui::Begin("ControlPanel",&showPlot,maximized);
				
				
				ImGui::InputText("IP:",IP_,IM_ARRAYSIZE(IP_));
				if(ImGui::Button("Conectar")){
					sensor = new Axia80M50(IP_);
					sensor->init();
					LOGS += ("\nSENSOR : "+std::string( sensor->__INIT__? "ON":"OFF" ));
				}
				if(ImGui::Button("BIAS")){
					sensor->bias();
					LOGS += "\nSensor: Calibrated";
				}

				if(ImGui::Button("CLEAR")){
					time = 0;
					for(int i = 0 ; i < 6 ; i++){
						items[i].data.clear();
					}
					LOGS += "\nDATA: Cleared";
				}
				ImGui::SameLine();
				if(ImGui::Button("SAVE")){
						FILE *file;
						file = fopen("out.txt","w");
						if(file != NULL){
							for (int i = 0 ; i < items[0].data.size() ; i++){
								fprintf(file,"%E\t",items[0].data[i].x);	
								for (int j = 0 ; j < 6 ; j++){
									fprintf(file,"%E\t",items[j].data[i].y);	
								}
								fprintf(file,"\n");	
							}
							
							fclose(file);
						}
				}

				
				if(ImGui::Checkbox("RUN",&RUNNING)){
					if(sensor->__INIT__ == false){
						LOGS += "\nFAIL: Please connect the sensor";
						RUNNING = false;
					}else{
						LOGS += "\nPlot: is " + std::string(RUNNING? "Running":"Stop");
					}
					
				}		


			ImGui::End();


			ImGui::Begin("SCOPE",&close,maximized|ImGuiWindowFlags_AlwaysAutoResize);
			
			
			static long count = 0;
			static std::ostringstream text;
			if(RUNNING){
				sensor->peek();
				for(int i = 0 ; i < 6 ; i++){
					items[i].data.push_back( ImVec2(time ,  sensor->values.raw[i]  ) );
				}
				if((count++ % 20)== 0){
					text.str("");
					text.precision(2);
					text  << "Fx: " << ((sensor->values.raw[0]>.4f || sensor->values.raw[0]<-.4f)? sensor->values.raw[0] : 0 )<< "N\n";
					text  << "Fy: " << ((sensor->values.raw[1]>.4f || sensor->values.raw[1]<-.4f)? sensor->values.raw[1] : 0 )<< "N\n";
					text  << "Fz: " << ((sensor->values.raw[2]>.4f || sensor->values.raw[2]<-.4f)? sensor->values.raw[2] : 0 )<< "N\n";
					text  << "Tx: " << ((sensor->values.raw[3]>.4f || sensor->values.raw[3]<-.4f)? sensor->values.raw[3] : 0 )<< "Nm\n";
					text  << "Ty: " << ((sensor->values.raw[4]>.4f || sensor->values.raw[4]<-.4f)? sensor->values.raw[4] : 0 )<< "Nm\n";
					text  << "Tz: " << ((sensor->values.raw[5]>.4f || sensor->values.raw[5]<-.4f)? sensor->values.raw[5] : 0 )<< "Nm\n";
				}
				
				
				ImGui::Begin("ControlPanel");
				ImGui::Text(text.str().c_str());
				ImGui::End();
			}
			
			ImGui::Plot("SCOPE", SCOPE, items); 

			ImGui::End();


			ImGui::Begin("LOG",&showPlot,maximized);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::Text(LOGS.c_str());
			ImGui::End();
			

		
			time += ImGui::GetIO().DeltaTime;

			if(!close) break;

		}

     
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();



	

	return 0;
}
