#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Shaders/LoadShaders.h"
GLuint h_ShaderProgram; // handle to shader program
GLint loc_ModelViewProjectionMatrix, loc_primitive_color; // indices of uniform variables

// include glm/*.hpp only if necessary
//#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale, ortho, etc.
glm::mat4 ModelViewProjectionMatrix;
glm::mat4 ViewMatrix, ProjectionMatrix, ViewProjectionMatrix;

#define TO_RADIAN 0.01745329252f  
#define TO_DEGREE 57.295779513f
#define BUFFER_OFFSET(offset) ((GLvoid *) (offset))

#define LOC_VERTEX 0

int win_width = 0, win_height = 0; 
float centerx = 0.0f, centery = 0.0f;
int leftbuttonpressed = 0;
int rightbuttonpressed = 0;

// 2D 물체 정의 부분은 objects.h 파일로 분리
// 새로운 물체 추가 시 prepare_scene() 함수에서 해당 물체에 대한 prepare_***() 함수를 수행함.
// (필수는 아니나 올바른 코딩을 위하여) cleanup() 함수에서 해당 resource를 free 시킴.
#include "objects.h"

unsigned int timestamp = 0;
void timer(int value) {
	timestamp = (timestamp + 1) % UINT_MAX;
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}


float airplane_x = 0.0;
float airplane_y = 200.0;
float airplane_x2 = 0.0;
float airplane_y2 = 210.0;
int check_c = 0;
int check_cok = 0;
float car_x = 0;
float car_y = -270;
int am = 1;
int r_rain = 0;
int s_snow = 0;
int q = 0;
int random_cok = 0;
int random_cake = 0;
int random_cake2 = 0;
int random_cok2 = 0;
int random_sword = 0;
int random_cok3 = 0;
int lv = 1;
int fill_gauge = 0;

int scale_cake = 0;
int scale_cake2 = 0;
int scale_cocktail = 0;
int scale_cocktail2 = 0;
int scale_hat = 0;
int scale_shirt = 0;
int scale_sword = 0;

int car2_x = 0;

int spacebar = 0;
int space_time = timestamp;

int level_time = timestamp;
int print_level = 0;

int game_over = 3;

void display(void) {
	glm::mat4 ModelMatrix;

	glClear(GL_COLOR_BUFFER_BIT);


	int cloud_clock = (timestamp % 5000) - 2500;

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 200, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(cloud_clock * 0.4), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(7, 3.5, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (20 * TO_RADIAN), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if (am == 0) draw_cloud3();
	else draw_cloud();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-150, 180, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(cloud_clock * 0.4), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5.5, 2.5, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (20 * TO_RADIAN), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if (am == 0) draw_cloud3();
	else draw_cloud2();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(200, 260, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(cloud_clock * 0.4), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 4, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (20 * TO_RADIAN), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if (am == 0) draw_cloud3();
	else draw_cloud();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-580, 240, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(cloud_clock * 0.4), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(9, 4, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (15 * TO_RADIAN), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if (am == 0) draw_cloud3();
	else draw_cloud2();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(400, 200, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(cloud_clock * 0.4), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 3, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, (20 * TO_RADIAN), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if (am == 0) draw_cloud3();
	else draw_cloud2();

	int airplane_clock = (timestamp % 1442) / 2 - 360; // -360 <= house_clock <= 360 
	float rotation_angle_airplane = atanf(100.0f * TO_RADIAN * cosf(airplane_clock * TO_RADIAN));
	float scaling_factor_airplane = fabs(cosf(airplane_clock * TO_RADIAN) + 1.0);

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 210, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(airplane_clock * 4), (float)(airplane_clock * 0.6), 0.0f));
	airplane_x = centerx + (float)(airplane_clock * 4);
	//airplane_y = 210;
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaling_factor_airplane, scaling_factor_airplane, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, 100.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	//draw_house(); // in WC
	draw_airplane2();



	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 150, 0.0f));
	airplane_x2 = centerx - (float)(airplane_clock * 2);
	if (airplane_x2 <= 0) {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(float)(airplane_clock * 2), -(float)(airplane_clock), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, (airplane_clock * 3 + 270) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2 - (float)(airplane_clock) / 120.0, 2 - (float)(airplane_clock) / 120.0, 1.0f));
	}
	else {
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(float)(airplane_clock * 2), (float)(airplane_clock * 0.3), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 260.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0, 1.0f));
	}
	//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_airplane();

	int bird_clock = (timestamp % 1800) / 2 - 450;
	float rotation_angle_bird = atanf(100.0f * TO_RADIAN * cosf(bird_clock * TO_RADIAN));
	float scaling_factor_bird = fabs(cosf(bird_clock * TO_RADIAN) + 1.0);
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 100, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-(float)(bird_clock), 50.0f * sinf(bird_clock * TO_RADIAN), 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(sinf(bird_clock * TO_RADIAN) + 1.8f, sinf(bird_clock * TO_RADIAN) + 1.8f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_bird();

	int car_clock = timestamp % 1000 - 500;
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, -290, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(car_clock * 3), 0.0f, 0.0f));
	car2_x = (float)(car_clock * 2);
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_car();


	int move_clock = (timestamp % 1442) / 2 - 360;

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(600, -230, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(move_clock * 3), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.7, 0.9, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_building();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-600, -250, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(move_clock * 3), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_house();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(270, -250, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(move_clock * 3), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_house();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-300, -295, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(move_clock * 3), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 6, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_tree2();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(160, -290, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(move_clock * 3), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(7, 7, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_tree2();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-260, -300, 0.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3((float)(move_clock * 3), 0.0f, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(6, 5, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_tree();


	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-35 + car_x, car_y + 40, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(7, 5, 1.0f));
	if (spacebar == 1) {
		if (sinf((timestamp - space_time) * 3 * TO_RADIAN) > 0) {
			ModelMatrix = glm::rotate(ModelMatrix, (20) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_basket();


	if (airplane_x == 0.0) check_c = 1;

	if (airplane_x > 600 || airplane_x < -600) check_c = 0;

	if (check_c == 1) {
		int cake_clock = timestamp % 720;
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(airplane_x, airplane_y, 0.0f));
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(airplane_x - (float)(cake_clock * 0.2), airplane_y - (float)(cake_clock * 4), 0.0f));
		if (cake_clock == 0) scale_hat = 0;
		if (cake_clock == 100) {
			if (car_x <= 230 && car_x >= 150) {
				fill_gauge++;
				scale_hat = 1;
			}
		}
		if (scale_hat == 1)
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0, 0, 1.0f));
		else
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3((float)(cake_clock) / 80.0, (float)(cake_clock) / 80.0, 1.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -(cake_clock * 2) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_hat();
	}

	if (airplane_x2 == 0.0) check_cok = 1;
	if (airplane_x2 > 600 || airplane_x2 < -600) check_cok = 0;

	if (check_cok == 1) {
		int shirt_clock = timestamp % 720;
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(airplane_x2, airplane_y2, 0.0f));
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(airplane_x2 + (float)(shirt_clock * 0.2), airplane_y2 - (float)(shirt_clock * 2), 0.0f));
		if (shirt_clock == 0) scale_shirt = 0;
		if (shirt_clock == 220) {
			if (car_x >= -200 && car_x <= -120) {
				fill_gauge++;
				scale_shirt = 1;
			}
		}
		if (scale_shirt == 1)
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0, 0, 1.0f));
		else
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3((float)(shirt_clock) / 100.0, (float)(shirt_clock) / 100.0, 1.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -(shirt_clock)*TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_shirt();
	}


	int drop_clock = timestamp % 180;
	if (drop_clock == 0)
		random_cok = rand() % 800 - 400;

	int cocktail_clock = timestamp % 360;
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cok, 400, 0.0f));
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cok, 400 - (float)(cocktail_clock * 4 - lv * 0.2), 0.0f));
	if (cocktail_clock == 0) scale_cocktail = 0;
	if (cocktail_clock == 160) {
		if (random_cok >= car_x - 50 && random_cok <= car_x + 50) {
			fill_gauge++;
			scale_cocktail = 1;
		}
	}
	if (scale_cocktail == 1)
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0, 0, 1.0f));
	else
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, 2, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, -(cocktail_clock)*TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_cocktail();


	int drop_clock2 = timestamp % 360;
	if (drop_clock2 == 0)
		random_cake = rand() % 800 - 400;
	int cake_clock = timestamp % 720;
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cake, 400, 0.0f));
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cake, 400 - (float)(cake_clock * 2 - lv * 0.2), 0.0f));
	if (cake_clock == 0) scale_cake = 0;
	if (cake_clock == 320) {
		if (random_cake >= car_x - 50 && random_cake <= car_x + 50) {
			fill_gauge++;
			scale_cake = 1;
		}
	}
	if (scale_cake == 1)
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0, 0, 1.0f));
	else
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, 2, 1.0f));
	//ModelMatrix = glm::rotate(ModelMatrix, -(cake_clock)*TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 shearingMat = glm::mat4x4(1.0);
	shearingMat[0][1] = sinf((cake_clock)*TO_RADIAN);
	shearingMat[1][0] = cosf((cake_clock)*TO_RADIAN);
	ModelMatrix *= shearingMat;
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_cake();


	int drop_clock3 = timestamp % 360 - 180;
	if (drop_clock3 == -180)
		random_cake2 = rand() % 800 - 400;
	int cake2_clock = timestamp % 720;
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cake2, 400, 0.0f));
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cake2, 400 - (float)(cake2_clock * 3 - lv * 0.2), 0.0f));
	if (cake2_clock == 0) scale_cake2 = 0;
	if (cake2_clock == 213) {
		if (random_cake2 >= car_x - 50 && random_cake2 <= car_x + 50) {
			fill_gauge++;
			scale_cake2 = 1;
		}
	}
	if (scale_cake2 == 1)
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0, 0, 1.0f));
	else
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, 2, 1.0f));
	//ModelMatrix = glm::rotate(ModelMatrix, -(cocktail_clock*2)*TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 shearingMat2 = glm::mat4x4(1.0);
	shearingMat2[0][1] = sinf((cake2_clock * 2) * TO_RADIAN);
	shearingMat2[1][0] = cosf((cake2_clock * 2) * TO_RADIAN);
	ModelMatrix *= shearingMat2;
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_cake2();

	int drop_clock4 = timestamp % 800 - 400;
	if (drop_clock4 == 0)
		random_sword = rand() % 800 - 400;
	int sword_clock = timestamp % 800 - 400;
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_sword, 400, 0.0f));
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_sword, 400 - (float)(sword_clock * 3 - lv * 0.2), 0.0f));
	if (sword_clock == 0) scale_sword = 0;
	if (sword_clock == 213) {
		if (random_sword >= car_x - 50 && random_sword <= car_x + 50) {
			fill_gauge = fill_gauge - 4;
			if (fill_gauge < 0) {
				game_over--;
				fill_gauge = 0;
			}
			scale_sword = 1;
		}
	}
	if (scale_sword == 1)
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0, 0, 1.0f));
	else
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(sinf(sword_clock * TO_RADIAN) * 2.0, 2, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, 180 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_sword();

	int drop_clock5 = timestamp % 720 - 360;
	if (drop_clock5 == 0)
		random_cok3 = rand() % 800 - 400;
	int cok3_clock = timestamp % 360 - 180;
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cok3, 400, 0.0f));
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(random_cok3, 400 - (float)(cok3_clock * 4 - lv * 0.2), 0.0f));
	if (cok3_clock == 0) scale_cocktail2 = 0;
	if (cok3_clock == 160) {
		if (random_cok3 >= car_x - 50 && random_cok3 <= car_x + 50) {
			fill_gauge++;
			scale_cocktail2 = 1;
		}
	}
	if (scale_cocktail2 == 1)
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0, 0, 1.0f));
	else
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, 2, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, -(cocktail_clock)*TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_cocktail2();



	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, -360, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(4, 0.2, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_land();


	if (spacebar == 1) {
		if (timestamp == space_time + 100) spacebar = 0;
		if (sinf((timestamp - space_time) * 3 * TO_RADIAN) > 0) {
			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(car_x, -270 + (float)(sinf((timestamp - space_time) * 3 * TO_RADIAN)) * 200, 0.0f));
			car_y = -270 + (float)(sinf((timestamp - space_time) * 3 * TO_RADIAN)) * 200;
			ModelMatrix = glm::rotate(ModelMatrix, (20) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		else {
			ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(car_x, -270, 0.0f));
			car_y = -270;
		}
	}
	else {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(car_x, -270, 0.0f));
		car_y = -270;
		//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5, 5, 1.0f));
	}
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5, 5, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_car2();
	//draw_basket2();


	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-35 + car_x, car_y + 40, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(7, 5, 1.0f));
	if (spacebar == 1) {
		if (sinf((timestamp - space_time) * 3 * TO_RADIAN) > 0) {
			ModelMatrix = glm::rotate(ModelMatrix, (20) * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_basket2();

	



	if (r_rain == 1) {
		int rain_clock = timestamp % 400 - 200;
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3((float)(rain_clock * 0.2), -(float)(rain_clock * 4), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rain();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-200 + (float)(rain_clock * 0.2), -(float)(rain_clock * 4), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rain();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(300 + (float)(rain_clock * 0.3), -(float)(rain_clock * 4), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rain();

		int rain_clock2 = timestamp % 200 - 100;
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-300, -(float)(rain_clock2 * 8), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rain();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-100 + (float)(rain_clock2 * 0.3), -(float)(rain_clock2 * 8), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rain();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(200 + (float)(rain_clock2 * 0.3), -(float)(rain_clock2 * 8), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_rain();
	}

	if (s_snow == 1) {
		int snow_clock = timestamp % 800 - 400;
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(200 + (float)(snow_clock * 0.3), -(float)(snow_clock * 2), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_snow();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-200 + (float)(snow_clock * 0.3), -(float)(snow_clock * 2), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_snow();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0 + (float)(snow_clock * 0.3), -(float)(snow_clock * 2), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_snow();


		int snow_clock2 = timestamp % 1600 - 800;
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(280 + (float)(snow_clock2 * 0.3), -(float)(snow_clock2), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_snow();


		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-100 + (float)(snow_clock2 * 0.3), -(float)(snow_clock2), 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(3, 3, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_snow();
	}


	if (game_over >= 0) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(200, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_gauge_box();

		if (fill_gauge >= 1)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(216, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 2)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(232, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 3)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(248, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 4)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(264, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 5)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(280, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 6)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(296, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 7)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(312, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 8)
			draw_gauge();

		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(328, 320, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(8, 8, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if (fill_gauge >= 9)
			draw_gauge();
	}
	
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(230, 240, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3((float)(5*sinf(timestamp*3*TO_RADIAN)), 4.5, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if(game_over>=1)
	draw_diamond();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(280, 240, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3((float)(5 * sinf(timestamp * 3 * TO_RADIAN)), 4.5, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if(game_over>=2)
	draw_diamond();

	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(330, 240, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3((float)(5 * sinf(timestamp * 3 * TO_RADIAN)), 4.5, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	if(game_over>=3)
	draw_diamond();

	if (fill_gauge > 9) {
		lv++;
		fprintf(stdout, "\n*****LEVEL UP!*****\n");
		fprintf(stdout, "Current Level : %d\n", lv);
		fill_gauge = 0;
		//level_time = timestamp / 10;
		print_level = 1;
		level_time = timestamp;
	}

	if (print_level == 1) {
		//level_time = timestamp;
		if (timestamp == level_time + 200) print_level = 0;
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-250, 0, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2, (float)((timestamp-level_time)/150.0)+1.0f, 1.0f));
		//ModelMatrix = glm::rotate(ModelMatrix, (level_time)*TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		if(game_over>=0)
			draw_level();
	}


	if (game_over < 0) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-180, 0, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.5, 1.5, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_gameover();
	}



	//glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Hello, world!");

	glFlush();	
}   

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESC key
		q = 1;
		glutLeaveMainLoop(); // Incur destuction callback for cleanups.
		break;
	case 'd':
		am = 0;
		glClearColor(0 / 255.0f, 0 / 255.0f, 0 / 255.0f, 1.0f);
		break;
	case 'l':
		am = 1;
		r_rain = 0;
		s_snow = 0;
		glClearColor(191 / 255.0f, 233 / 255.0f, 249 / 255.0f, 1.0f);
		break;
	case 'r':
		r_rain = 1;
		break;
	case 's':
		s_snow = 1;
		break;
	case 32:
		spacebar = 1;
		space_time = timestamp;
		break;
	}
}

//int leftbuttonpressed = 0;
void mouse(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		leftbuttonpressed = 1;
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		leftbuttonpressed = 0;
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		rightbuttonpressed = 1;
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {
		rightbuttonpressed = 0;
	}
}

void motion(int x, int y) {
	if (leftbuttonpressed) {
		centerx =  x - win_width/2.0f, centery = (win_height - y) - win_height/2.0f;
		glutPostRedisplay();
	}
} 

void reshape(int width, int height) {
	win_width = width, win_height = height;
	
  	glViewport(0, 0, win_width, win_height);
	ProjectionMatrix = glm::ortho(-win_width / 2.0, win_width / 2.0, 
		-win_height / 2.0, win_height / 2.0, -1000.0, 1000.0);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	update_axes();

	glutPostRedisplay();
}

void cleanup(void) {
	glDeleteVertexArrays(1, &VAO_axes);
	glDeleteBuffers(1, &VBO_axes);

	glDeleteVertexArrays(1, &VAO_airplane);
	glDeleteBuffers(1, &VBO_airplane);

	glDeleteVertexArrays(1, &VAO_house);
	glDeleteBuffers(1, &VBO_house);

	glDeleteVertexArrays(1, &VAO_car);
	glDeleteBuffers(1, &VBO_car);

	glDeleteVertexArrays(1, &VAO_car2);
	glDeleteBuffers(1, &VBO_car2);

	glDeleteVertexArrays(1, &VAO_shirt);
	glDeleteBuffers(1, &VBO_shirt);

	glDeleteVertexArrays(1, &VAO_hat);
	glDeleteBuffers(1, &VBO_hat);

	glDeleteVertexArrays(1, &VAO_cocktail);
	glDeleteBuffers(1, &VBO_cocktail);

	glDeleteVertexArrays(1, &VAO_cake);
	glDeleteBuffers(1, &VBO_cake);

	glDeleteVertexArrays(1, &VAO_sword);
	glDeleteBuffers(1, &VBO_sword);

	glDeleteVertexArrays(1, &VAO_tree);
	glDeleteBuffers(1, &VBO_tree);

	glDeleteVertexArrays(1, &VAO_building);
	glDeleteBuffers(1, &VBO_building);

	glDeleteVertexArrays(1, &VAO_basket);
	glDeleteBuffers(1, &VBO_basket);

	glDeleteVertexArrays(1, &VAO_basket2);
	glDeleteBuffers(1, &VBO_basket2);

	glDeleteVertexArrays(1, &VAO_cloud);
	glDeleteBuffers(1, &VBO_cloud);

	glDeleteVertexArrays(1, &VAO_bird);
	glDeleteBuffers(1, &VBO_bird);

	glDeleteVertexArrays(1, &VAO_snow);
	glDeleteBuffers(1, &VBO_snow);

	glDeleteVertexArrays(1, &VAO_rain);
	glDeleteBuffers(1, &VBO_rain);

	glDeleteVertexArrays(1, &VAO_gauge_box);
	glDeleteBuffers(1, &VBO_gauge_box);

	glDeleteVertexArrays(1, &VAO_gauge);
	glDeleteBuffers(1, &VBO_gauge);

	glDeleteVertexArrays(1, &VAO_level);
	glDeleteBuffers(1, &VBO_level);

	glDeleteVertexArrays(1, &VAO_diamond);
	glDeleteBuffers(1, &VBO_diamond);

	glDeleteVertexArrays(1, &VAO_game);
	glDeleteBuffers(1, &VBO_game);
}


void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (leftbuttonpressed) car_x = car_x - (9 + lv);
		else car_x = car_x - (5 + lv);
		break;
	case GLUT_KEY_RIGHT:
		if (leftbuttonpressed) car_x = car_x + (9 + lv);
		else car_x = car_x + (5 + lv);
		break;
	}
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutTimerFunc(10, timer, 0);
	glutCloseFunc(cleanup);
}

void prepare_shader_program(void) {
	ShaderInfo shader_info[3] = {
		{ GL_VERTEX_SHADER, "Shaders/simple.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
		{ GL_NONE, NULL }
	};

	h_ShaderProgram = LoadShaders(shader_info);
	glUseProgram(h_ShaderProgram);

	loc_ModelViewProjectionMatrix = glGetUniformLocation(h_ShaderProgram, "u_ModelViewProjectionMatrix");
	loc_primitive_color = glGetUniformLocation(h_ShaderProgram, "u_primitive_color");
}

void initialize_OpenGL(void) {
	glEnable(GL_MULTISAMPLE); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glClearColor(191 / 255.0f, 233 / 255.0f, 249 / 255.0f, 1.0f);

	ViewMatrix = glm::mat4(1.0f);

}

void prepare_scene(void) {
	prepare_axes();
	prepare_airplane();
	prepare_house();
	prepare_car();
	prepare_car2();
	prepare_shirt();
	prepare_hat();
	prepare_cocktail();
	prepare_cake();
	prepare_sword();
	prepare_tree();
	prepare_land();
	prepare_building();
	prepare_basket();
	prepare_basket2();
	prepare_cloud();
	prepare_bird();
	prepare_snow();
	prepare_rain();
	prepare_gauge_box();
	prepare_gauge();
	prepare_level();
	prepare_diamond();
	prepare_gameover();
}

void initialize_renderer(void) {
	register_callbacks();
	prepare_shader_program(); 
	initialize_OpenGL();
	prepare_scene();
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = GL_TRUE;

    error = glewInit();
	if (error != GLEW_OK) { 
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char *program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
	fprintf(stdout, "    This program was coded for CSE4170 students\n");
	fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}

#define N_MESSAGE_LINES 2
int main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 Simple2DTransformationMotion_GLSL_3.0.3";
	char messages[N_MESSAGE_LINES][256] = {
		"    - Keys used: 'ESC', 'r', 's', 'd', 'l', '<-', '->'\n"
		"    - Mouse used: L-click"
	};

	glutInit (&argc, argv);
 	glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize (800, 800);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

	fprintf(stdout, "Current Level : %d\n", lv);


	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}


