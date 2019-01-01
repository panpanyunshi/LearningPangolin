#include <iostream>
#include <pangolin/pangolin.h>
#include <stdio.h>      /* printf */
#include <math.h>       /* sin */

// example:
//https://www.cnblogs.com/feifanrensheng/p/8628900.html
//https://github.com/stevenlovegrove/Pangolin/blob/master/examples/SimpleDisplay/main.cpp


void pangolin_show_plt(void);
void pangolin_show_3d(void);

int main(/*int argc, char* argv[]*/) {
    std::cout << "Hello, World!" << std::endl;

    // Create OpenGL window in single line
    pangolin::CreateWindowAndBind("Main",640,480);
//    pangolin_show_plt();

    pangolin_show_3d();

    return 0;
}

void pangolin_show_3d(void){
    // Define Camera Render Object (for view / scene browsing)
// depth min and max bound
    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(640,480,420,420,320,240,0.1,1000),   //[w h] [fu  fv  u0  v0] [zNear zFar]
            pangolin::ModelViewLookAt(-0,0.5,-3, 0,0,0, pangolin::AxisY)    // https://blog.csdn.net/ivan_ljf/article/details/8764737
    );


    const int UI_WIDTH = 180;
    // Add named OpenGL viewport to window and provide 3D Handler
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, -640.0f/480.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));        // left save ui space

    // Add named Panel and bind to variables beginning 'ui'
    pangolin::CreatePanel("ui")
            .SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));

    pangolin::Var<bool> a_button("ui.A_Button",false,false);
    pangolin::Var<bool> save_cube("ui.Save_Cube",false,false);

    while( !pangolin::ShouldQuit() ){
        // Clear entire screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if( pangolin::Pushed(a_button) )
            std::cout << "You Pushed a button!" << std::endl;

        if( pangolin::Pushed(save_cube) ){
            d_cam.SaveOnRender("cube");
        }

        // Activate efficiently by object
        d_cam.Activate(s_cam);

        // Render some stuff
//        glColor3f(1.0,0.0,0.0);
        pangolin::glDrawColouredCube();

        pangolin::FinishFrame();
    }

}


void pangolin_show_plt(void)
{

    // Data logger object
    pangolin::DataLog log;
    // Optionally add named labels
    std::vector<std::string> labels;
    labels.push_back(std::string("sin(t)"));
    labels.push_back(std::string("cos(t)"));
    labels.push_back(std::string("sin(t)+cos(t)"));
    log.SetLabels(labels);

    float t = 0;
    const float tinc = 0.01f;
    int UI_WIDTH = 180;
    // OpenGL 'view' of data. We might have many views of the same data.
    // log  [x_dlim x_ulim y_dlim y_ulim] [x_tick y_tick] the scale of frame
    pangolin::Plotter plotter(&log,0.0f,4.0f*(float)M_PI/tinc,-2.0f,2.0f /*, (float)M_PI/(4.0f*tinc),0.5f*/);
    // [bottom  top  left  right scale]   fractional
    // pixel coordinates, scale pos->small, neg->big {>1 y-axis} {<1 x-axis}
    plotter.SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, 1.0);  // how much space the plotter is taken
    plotter.Track("$i");    // window is tracked, not fixed.

    pangolin::CreatePanel("ui")
            .SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));


    pangolin::Var<bool> a_checkbox("ui.A_Checkbox",false,true);
    pangolin::Var<bool> save_cube("ui.Save_Cube",false,false);


    pangolin::DisplayBase().AddDisplay(plotter);

    // Default hooks for exiting (Esc) and fullscreen (tab).
    bool is_pause = false;
    while( !pangolin::ShouldQuit() )
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if( pangolin::Pushed(save_cube) )
        {
            is_pause = !is_pause;
        }
        if(is_pause){
            usleep(1000);
        }
        else{
            if( a_checkbox )  printf("current time: %f\n", t);
            log.Log(sin(t),cos(t),sin(t)+cos(t), sin(2*t));
            t += tinc;
        }

        // Render graph, Swap frames and Process Events
        pangolin::FinishFrame();
    }
}
