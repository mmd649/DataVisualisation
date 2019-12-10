/*
	This is the source code for the data visualisation coursework. I tried to explain what I did as much as I could 
	by inline commenting but may have missed some. There may have some line of code that has no comments but that is most
	probably because the code is self explanatory.
	
	-Mark Medrano
*/


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/Shader.h"
#include "Data/Data.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

//window size settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 800;

//Default year of 1991, change if necessary (1991, 2001, 2011)
int year_to_visualise = 1991;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 800.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


/*
	Raw screen coordinates for each given location

	To get the coordinates of each of this location, I used the function glfwGetCursorPos(). With the help of google maps, i searched each location
	individually and the pointed the mouse cursor to that specific location. The function glfwGetCursorPos() returns the and xpos and ypos of where
	the mouse cursor is within the window.
*/
int rawMapCoordinates[] = {
	573, 639, //London 
	498, 559, //Birmingham
	434, 312, //Glasgow
	465, 491, //Liverpool
	459, 628, //Bristol
	513, 501, //Sheffield
	483, 485, //Manchester
	532, 467, //Leeds
	485, 320, //Edinburgh
	536, 557, //Leicester
	511, 474, //Bradford
	418, 615, //Cardiff
	517, 578, //Coventry
	554, 528, //Nottingham
	587, 480, //Kingston-Upon-Hull
	343, 391, //Belfast
	494, 528, //Stoke-On-Trent
	542, 393, //New Castle
	527, 537, //Derby
	508, 673, //Southampton
	515, 681, //Portsmouth
	366, 692, //Plymouth
	569, 685, //Brighton And Hove
	536, 639, //Reading
	548, 574, // Northampton
	560, 610, //Luton
	485, 554, //Wolverhampton
	544, 237, //Aberdeen
	486, 485, //Bolton
	472, 680, //Bournemouth
	650, 570, //Norwich
	488, 632, //Swindon
	383, 607, //Swansea
	617, 637, //Southend-On-Sea
	558, 425, //Midlesbrough
	547, 401, //Sunderland
	548, 600, //Milton Keynes
	480, 498, //Warrington
	516, 481, //Huddersfield
	596, 481, //Peterborough
	520, 608, //Oxford
	551, 640, //Slough
	479, 677, //Poole
	557, 469, //York
	467, 466, //Blackpool
	509, 273, //Dundee
	589, 582, //Cambridge
	645, 598, //Ipswich
	457, 497, //Birkenhead
	474, 542, //Telford
	482, 608, //Gloucester
	480, 500, //Sale <-- ?
	560, 621, //Watford <-- ?
	435, 600, //Newport
	508, 572, //Solihull
	543, 624, //High Wycombe
	544, 395, //Gateshead
	622, 613, //Colchester
	493, 470, //Blackburn
	484, 600, //Cheltenham
	395, 656, //Exeter
	600, 622, //Chelmsford
	564, 496, //Doncaster
	541, 504, //Rotherham
	589, 688, //Eastbourne
	551, 686, //Worthing
	505, 556, //Sutton Coldfield <-- ?
	501, 487, //Rochdale
	603, 662, //Maidstone
	517, 651, //Basingstoke
	589, 623, //Basildon <-- ?
	569, 667, //Crawley 
	500, 500, //Stockport
	548, 654, //Woking
	597, 657, //Gillingham <-- ?
	491, 487, //Salford <-- ?
	470, 495, //Wigan
	469, 493, //St Helens
	585, 520, //Lincoln
	481, 578 //Worcester
};

int main()
{
	// glfw initialisation and configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// glfw window creation
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Data Visualisation", NULL, NULL);
	//just a simple error check
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	//Initialize data object to load data
	Data *populationData = new Data();

	//Read file
	populationData->readData();

	//populationData->determineMinMax();

	//normalised population data
	populationData->normalisedPopulationData();

	/*std::cout << "Please choose a year to visualise" << std::endl;
	std::cin >> year_to_visualise;*/

	populationData->showYearPopulationDetails(year_to_visualise);

	// build and compile all the shader programs to be used
	Shader mapShader("..\\OpenGL\\src\\Shader\\GLSL\\vertexShader.txt", "..\\OpenGL\\src\\Shader\\GLSL\\fragmentShader.txt");
	Shader generalShader("..\\OpenGL\\src\\Shader\\GLSL\\generalVertexShader.txt", "..\\OpenGL\\src\\Shader\\GLSL\\generalFragmentShader.txt");
	Shader populationShader("..\\OpenGL\\src\\Shader\\GLSL\\populationVertexShader.txt", "..\\OpenGL\\src\\Shader\\GLSL\\populationFragmentShader.txt");

	//Rectangle Face Vertices
	float rectangleFace[] = {
	-0.8f,  0.8f, 0.0f,		0.0f, 1.0f, //Top Left (face)
	 0.8f,  0.8f, 0.0f,		1.0f, 1.0f,	//Top Right (face)
	-0.8f, -0.8f, 0.0f,		0.0f, 0.0f,	//Bottom Left (face)
	 0.8f,  0.8f, 0.0f,		1.0f, 1.0f,	//Top Right (face)
	 0.8f, -0.8f, 0.0f,		1.0f, 0.0f,	//Bottom Right (face) 
	-0.8f, -0.8f, 0.0f,		0.0f, 0.0f	//Bottom Left (face)
	};

	//Rest of rectangle sides vertices
	float rectangleSides[] = {
									
		-0.8f,  0.8f, -0.15f,	//Top Left (back)
		 0.8f,  0.8f, -0.15f,	//Top Right (back)	
		-0.8f, -0.8f, -0.15f,	//Bottom Left (back)
		 0.8f,  0.8f, -0.15f,	//Top Right	(back)
		 0.8f, -0.8f, -0.15f,	//Bottom Right (back)
		-0.8f, -0.8f, -0.15f,	//Bottom Left (back)

		-0.8f,  0.8f, -0.15f,	//Top Left (left side)
		-0.8f,  0.8f,  0.0f,	//Top Right (left side)
		-0.8f, -0.8f, -0.15f,	//Bottom Left (left side)
		-0.8f,  0.8f,  0.0f,	//Top Right (left side)
		-0.8f, -0.8f,  0.0f,	//Bottom Right (left side) 
		-0.8f, -0.8f, -0.15f,	//Bottom Left (left side)

		 0.8f,  0.8f,  0.0f,	//Top Left (right side)
		 0.8f,  0.8f, -0.15f,	//Top Right (right side)
		 0.8f, -0.8f,  0.0f,	//Bottom Left (right side)
		 0.8f,  0.8f, -0.15f,	//Top Right (right side)
		 0.8f, -0.8f, -0.15f,	//Bottom Right (right side) 
		 0.8f, -0.8f,  0.0f,	//Bottom Left (right side)

		-0.8f,  0.8f, -0.15f,	 //Far Left (top)
		 0.8f,  0.8f, -0.15f,	//Far Right (top)
		-0.8f,  0.8f,  0.0f,	//Near Left (top)
		 0.8f,  0.8f, -0.15f,	//Far Right (top)
		 0.8f,  0.8f,  0.0f,	//Near Right (top) 
		-0.8f,  0.8f,  0.0f,	//Near Left (top)

		-0.8f, -0.8f, -0.15f,	//Far Left (base)
		 0.8f, -0.8f, -0.15f,	//Far Right (base)
		-0.8f, -0.8f,  0.0f,	//Near Left (base)
		 0.8f, -0.8f, -0.15f,	//Far Right (base)
		 0.8f, -0.8f,  0.0f,	//Near Right (base) 
		-0.8f, -0.8f,  0.0f		//Near Left (base)
	};

	unsigned int rectangleFaceVBO, rectangleSidesVBO, rectangleFaceVAO, rectangleSidesVAO;

	//Generate VBO and VBA for rectangle face
	glGenVertexArrays(1, &rectangleFaceVAO);
	glGenBuffers(1, &rectangleFaceVBO);
	glBindVertexArray(rectangleFaceVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangleFaceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleFace), rectangleFace, GL_STATIC_DRAW);

	// position attribute in vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coord attribute  in vao
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//Generate VBO and VBA for rectangle sides
	glGenVertexArrays(1, &rectangleSidesVAO);
	glGenBuffers(1, &rectangleSidesVBO);
	glBindVertexArray(rectangleSidesVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectangleSidesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleSides), rectangleSides, GL_STATIC_DRAW);

	// position attribute in vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//normalised the raw screen coordinate to be used for world coordinates
	std::vector <float> normalisedCoordinates = populationData->toWorldCoordinates(rawMapCoordinates, 160, year_to_visualise, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Generate VBO and VBA for population visualisation
	unsigned int populationVBO, populationVBA;
	glGenVertexArrays(1, &populationVBA);
	glGenBuffers(1, &populationVBO);
	glBindVertexArray(populationVBA);
	glBindBuffer(GL_ARRAY_BUFFER, populationVBO);
	glBufferData(GL_ARRAY_BUFFER, (normalisedCoordinates.size() * sizeof(float)), &normalisedCoordinates[0], GL_STATIC_DRAW);

	// position attribute in vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//vector of the side coordinates 
	std::vector<float> sidesVertices = populationData->generateSides(rawMapCoordinates, 160, year_to_visualise, WINDOW_WIDTH, WINDOW_HEIGHT);

	//Generate VBO and VBA for 3D visualisation of population data
	unsigned int sidesVBO, sidesVBA;
	glGenVertexArrays(1, &sidesVBA);
	glGenBuffers(1, &sidesVBO);
	glBindVertexArray(sidesVBA);
	glBindBuffer(GL_ARRAY_BUFFER, sidesVBO);
	glBufferData(GL_ARRAY_BUFFER, sidesVertices.size() * sizeof(float), &sidesVertices[0], GL_STATIC_DRAW);

	// position attribute in vao
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	// load and create a texture 
	unsigned int mapTexture;
	glGenTextures(1, &mapTexture);
	glBindTexture(GL_TEXTURE_2D, mapTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("..\\Image\\uk_map_2.jpg", &width, &height, &nrChannels, 0);
	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}else{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// render loop
	while (!glfwWindowShouldClose(window)){
		// per-frame time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		//Background colour
		glClearColor(0.08f, 0.04f, 0.13f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Setup for camera for map shader
		mapShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		mapShader.setMat4("projection", projection);
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		mapShader.setMat4("view", view);


		//Render Rectangle Face and setup camera movement
		glBindVertexArray(rectangleFaceVAO);
		glm::mat4 model = glm::mat4(1.0f);
		mapShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		//render rest of rectangle
		generalShader.use();
		generalShader.setMat4("projection", projection);
		generalShader.setMat4("view", view);
		generalShader.setMat4("model", model);

		glBindVertexArray(rectangleSidesVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//render population data
		populationShader.use();
		populationShader.setMat4("projection", projection);
		populationShader.setMat4("view", view);
		populationShader.setMat4("model", model);

		glBindVertexArray(populationVBA);
		glDrawArrays(GL_TRIANGLES, 0, 480);

		glBindVertexArray(sidesVBA);
		glDrawArrays(GL_TRIANGLES, 0, 2400);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &rectangleFaceVAO);
	glDeleteBuffers(1, &rectangleFaceVBO);

	delete populationData;
	glfwTerminate();
	return 0;
}

// input processing
void processInput(GLFWwindow *window){
	//you can use esc key to close the window (does not work when you press esc in the console.)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//used to map the locations. Press 1 to see the screen coordinate of what you are looking at. (centre of screen / mouse position)
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "(" << xpos << ", " << ypos << ")" << std::endl;
	}

	float cameraSpeed = 2.5 * deltaTime;

	//When W is pressed
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	//When S is pressed
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	//When A is pressed
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	//When D is pressed
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

// callback function for camera. This function will execute whenever the camera is moved(via mouse or wasd or zoom function<mouse wheel> ).
void mouse_callback(GLFWwindow* window, double xpos, double ypos){

	if (firstMouse){

		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;


	if (pitch > 89.0f)
		pitch = 89.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){

	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;

	if (fov <= 1.0f)
		fov = 1.0f;

	if (fov >= 45.0f)
		fov = 45.0f;
}

