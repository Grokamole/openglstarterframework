/** This program is essentially a Hello World for OpenGL that includes a log file
and builds using GLEW and GLFW libraries.

@copyright Copyright 2018
@author Joseph Miller
*/
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <cstdlib>
#include <fstream>

static int s_windowWidth = 800;  ///< the openGL windows width
static int s_windowHeight = 600; ///< the openGL windows height

/** Initializes GLFW

@param[in] logFile an output filestream to use
@return nullptr if not successful, otherwise an initialized instance of GLFW
*/
GLFWwindow * InitializeGLFW( std::ofstream & logFile )
{
    // initialize GLFW
    if ( !glfwInit() )
    {
        logFile << "Error: could not initialize GLFW." << std::endl;
        return nullptr;
    }

    // Create GLFW window
    GLFWwindow* glfwWindow = glfwCreateWindow( s_windowWidth, s_windowHeight, "Hello World!", NULL, NULL );
    if ( nullptr == glfwWindow )
    {
        glfwTerminate();
        logFile << "Error: could not create GLFW window." << std::endl;
        return nullptr;
    }

    return glfwWindow;
}

/** Sets up an OpenGL GLFW window into the current context.

@param[in] glfwWindow the window to switch the context to.
@param[in] logFile    the log file to write output to if an error occurs
@retval true  if the window was set up correctly
@retval false if the window was not set up correctly
*/
bool SetupOpenGLWindow( GLFWwindow* const glfwWindow, std::ofstream & logFile )
{
    // make the current window context
    glfwMakeContextCurrent( glfwWindow );

    GLenum errorCode = glewInit();

    if ( GLEW_OK != errorCode )
    {
        glfwTerminate();
        logFile << "Error: " << glewGetErrorString( errorCode ) << std::endl;
        return false;
    }

    return true;
}

/** Runs the main OpenGL loop

@param glfwWindow a GLFW OpenGL window that is the current context.
@param logFile    the log file to use if an error occurs.
*/
void RunLoop( GLFWwindow* const glfwWindow, std::ofstream & logFile )
{
    // main loop
    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers
        glfwSwapBuffers(glfwWindow);

        // poll and process events
        glfwPollEvents();
    }
}

/** The main program entry point

@param argc[unused]
@param argv[unused]
@return Always returns EXIT_SUCCESS.
    @note Check log.txt file for errors.
*/
int main( int argc, char ** argv )
{
    std::ofstream logFile( "log.txt" );
    if ( !logFile.good() )
    {
        return EXIT_SUCCESS;
    }

    GLFWwindow* glfwWindow = InitializeGLFW( logFile );

    if ( nullptr == glfwWindow )
    {
        logFile.close();
        return EXIT_SUCCESS;
    }

    if ( !SetupOpenGLWindow( glfwWindow, logFile ) )
    {
        logFile.close();
    }

    logFile << "Success: Initialization successful with GL Version: " << glGetString( GL_VERSION ) << "\n"
            << "Starting main loop." << std::endl;

    RunLoop( glfwWindow, logFile );

    glfwTerminate();

    logFile << "Normal termination successful." << std::endl;
    logFile.close();

    return EXIT_SUCCESS;
}