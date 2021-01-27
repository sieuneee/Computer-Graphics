#include "my_geom_objects.h"

// callbacks
float PRP_distance_scale[6] = { 0.5f, 1.0f, 2.5f, 5.0f, 10.0f, 20.0f };

glm::mat4 world_light;

int flag_draw_screen, flag_screen_effect;
float screen_frequency, screen_width;
Material_Parameters material_screen;
GLint loc_screen_effect, loc_screen_frequency, loc_screen_width;
GLint loc_blind_effect;
int r_flag = 0;

int prevx, prevy;

int q_flag = 1;


typedef  struct _Camera {
	float pos[3];
	float uaxis[3], vaxis[3], naxis[3];
	float fovy, aspect_ratio, near_c, far_c;
	int move;
}Camera;

Camera camera;

glm::mat4 camera_view;

void set_ViewMatrix_from_camera_frame(void) {
	ViewMatrix = glm::mat4(camera.uaxis[0], camera.vaxis[0], camera.naxis[0], 0.0f,
		camera.uaxis[1], camera.vaxis[1], camera.naxis[1], 0.0f,
		camera.uaxis[2], camera.vaxis[2], camera.naxis[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	ViewMatrix = glm::translate(ViewMatrix, glm::vec3(-camera.pos[0], -camera.pos[1], -camera.pos[2]));
	//camera_view = ViewMatrix;
	glm::vec4 position_EC;
	glm::vec3 direction_EC;

	glUseProgram(h_ShaderProgram_TXPS);
	// Must update the light 1's geometry in EC.
	position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
		light[1].position[2], light[1].position[3]);
	glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
	direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0],
		light[1].spot_direction[1], light[1].spot_direction[2]);
	glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
	glUseProgram(0);
}

void initialize_camera(void) {
	camera.pos[0] = 750.0f; camera.pos[1] = 450.0f;  camera.pos[2] = 750.0f;
	camera.uaxis[0] = -0.5f; camera.uaxis[1] = 0.0f; camera.uaxis[2] = 0.5f;
	camera.vaxis[0] = 0.0f; camera.vaxis[1] = 0.5f; camera.vaxis[2] = 0.0f;
	camera.naxis[0] = 0.5f; camera.naxis[1] = 0.0f; camera.naxis[2] = 0.5f;

	camera.move = 0;
	camera.fovy = 60.0f, camera.aspect_ratio = 1.0f; camera.near_c = 100.0f; camera.far_c = 20000.0f;

	glm::vec4 position_EC;
	glm::vec3 direction_EC;
	position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
		light[1].position[2], light[1].position[3]);
	glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
	direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0],
		light[1].spot_direction[1], light[1].spot_direction[2]);
	glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);

	set_ViewMatrix_from_camera_frame();
	camera_view = ViewMatrix;
	glUseProgram(h_ShaderProgram_TXPS);
	// Must update the light 1's geometry in EC.
	position_EC = camera_view * glm::vec4(light[1].position[0], light[1].position[1],
		light[1].position[2], light[1].position[3]);
	glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
	direction_EC = glm::mat3(camera_view) * glm::vec3(light[1].spot_direction[0],
		light[1].spot_direction[1], light[1].spot_direction[2]);
	glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
	glUseProgram(0);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
}

enum axes { X_AXIS, Y_AXIS, Z_AXIS };
int flag_translation_axis;

#define CAM_TSPEED 0.05f
void renew_cam_position(int del) {
	switch (flag_translation_axis) {
	case X_AXIS:
		camera.pos[0] += CAM_TSPEED * del * (camera.uaxis[0]);
		camera.pos[1] += CAM_TSPEED * del * (camera.uaxis[1]);
		camera.pos[2] += CAM_TSPEED * del * (camera.uaxis[2]);
		break;
	case Y_AXIS:
		camera.pos[0] += CAM_TSPEED * del * (camera.vaxis[0]);
		camera.pos[1] += CAM_TSPEED * del * (camera.vaxis[1]);
		camera.pos[2] += CAM_TSPEED * del * (camera.vaxis[2]);
		break;
	case Z_AXIS:
		camera.pos[0] += CAM_TSPEED * del * (-camera.naxis[0]);
		camera.pos[1] += CAM_TSPEED * del * (-camera.naxis[1]);
		camera.pos[2] += CAM_TSPEED * del * (-camera.naxis[2]);
		break;
	}
}

#define CAM_RSPEED 0.1f
void renew_cam_orientation_rotation_around_v_axis(int angle) {
	// let's get a help from glm
	glm::mat3 RotationMatrix;
	glm::vec3 direction;

	if (flag_translation_axis == Z_AXIS) {
		RotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0), CAM_RSPEED * TO_RADIAN * angle,
			glm::vec3(camera.vaxis[0], camera.vaxis[1], camera.vaxis[2])));
	}
	else if (flag_translation_axis == Y_AXIS) {
		RotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0), CAM_RSPEED * TO_RADIAN * angle,
			glm::vec3(camera.naxis[0], camera.naxis[1], camera.naxis[2])));
	}
	else if (flag_translation_axis == X_AXIS) {
		RotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0), CAM_RSPEED * TO_RADIAN * angle,
			glm::vec3(camera.uaxis[0], camera.uaxis[1], camera.uaxis[2])));
	}

	direction = RotationMatrix * glm::vec3(camera.uaxis[0], camera.uaxis[1], camera.uaxis[2]);
	camera.uaxis[0] = direction.x; camera.uaxis[1] = direction.y; camera.uaxis[2] = direction.z;
	direction = RotationMatrix * glm::vec3(camera.vaxis[0], camera.vaxis[1], camera.vaxis[2]);
	camera.vaxis[0] = direction.x; camera.vaxis[1] = direction.y; camera.vaxis[2] = direction.z;
	direction = RotationMatrix * glm::vec3(camera.naxis[0], camera.naxis[1], camera.naxis[2]);
	camera.naxis[0] = direction.x; camera.naxis[1] = direction.y; camera.naxis[2] = direction.z;

}


void set_material_screen(void) {
	// assume ShaderProgram_PS is used
	glUniform4fv(loc_material.ambient_color, 1, material_screen.ambient_color);
	glUniform4fv(loc_material.diffuse_color, 1, material_screen.diffuse_color);
	glUniform4fv(loc_material.specular_color, 1, material_screen.specular_color);
	glUniform1f(loc_material.specular_exponent, material_screen.specular_exponent);
	glUniform4fv(loc_material.emissive_color, 1, material_screen.emissive_color);
}

void draw_screen(void) {
	glFrontFace(GL_CCW);

	glBindVertexArray(rectangle_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void initialize_screen(void) {
	flag_draw_screen = flag_screen_effect = 0;
	screen_frequency = 1.0f;
	screen_width = 0.125f;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(h_ShaderProgram_simple);
	ModelViewMatrix = glm::scale(ViewMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_simple, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glLineWidth(2.0f);
	draw_axes();
	glLineWidth(1.0f);


	glUseProgram(h_ShaderProgram_TXPS);
  	set_material_floor();

	if(r_flag==1)
		glUniform1i(loc_texture, TEXTURE_ID_RAINBOW);
	else {
		if (flag_texture_mapping == 1)
			glUniform1i(loc_texture, TEXTURE_ID_FLOOR);
		else
			glUniform1i(loc_texture, TEXTURE_ID_FLOOR_2);
	}
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-500.0f, 0.0f, 500.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(1000.0f, 1000.0f, 1000.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, -90.0f*TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_floor();

	if (flag_draw_screen) {
		set_material_screen();
		glUniform1i(loc_texture, TEXTURE_ID_SOGANG);
		ModelViewMatrix = glm::scale(ViewMatrix, glm::vec3(500.0f, 500.0f, 500.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);

		glUniform1i(loc_screen_effect, flag_screen_effect);
		draw_screen();
		glUniform1i(loc_screen_effect, 0);
	}
	
 	set_material_tiger();
	glUniform1i(loc_texture, TEXTURE_ID_TIGER);
	ModelViewMatrix = glm::rotate(ViewMatrix, -rotation_angle_tiger, glm::vec3(0.0f, 1.0f, 0.0f)); 
	ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(400.0f, 0.0f, 0.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, -90.0f*TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_tiger();

	glUseProgram(h_ShaderProgram_simple);
	ModelViewProjectionMatrix = glm::scale(ModelViewProjectionMatrix, glm::vec3(20.0f, 20.0f, 20.0f));
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_simple, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_axes();

	glUseProgram(h_ShaderProgram_TXPS);

	set_material_ben();
	glUniform1i(loc_texture, TEXTURE_ID_BEN);
	ModelViewMatrix = glm::rotate(ViewMatrix, -rotation_angle_tiger, glm::vec3(0.0f, 1.0f, 0.0f));
	if(r_flag==1) ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(350.0f, 0.0f, 200.0f));
	else ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(timestamp_scene%400, 0.0f, timestamp_scene%400));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(100.0f, -100.0f, -100.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_ben();


	set_material_wolf();
	glUniform1i(loc_texture, TEXTURE_ID_WOLF);
	ModelViewMatrix = glm::rotate(ViewMatrix, -rotation_angle_tiger,  glm::vec3(0.0f, 1.0f, 0.0f));
	ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(300.0f, 0.0f, 0.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(100.0f, 100.0f,100.0f));
	
	if(timestamp_scene % 360>180 && r_flag==0)
		ModelViewMatrix = glm::rotate(ModelViewMatrix, 10*(timestamp_scene%360)*TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_wolf();


	if (r_flag) {
		set_material_tiger();
		glUniform1i(loc_texture, TEXTURE_ID_SPIDER);
		ModelViewMatrix = glm::rotate(ViewMatrix, -rotation_angle_tiger, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(200.0f, 0.0f, -400.0f));
		//ModelViewMatrix = glm::rotate(ModelViewMatrix, -90.0f * TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(50.0f, -50.0f, 50.0f));
		ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
		ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

		glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
		glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
		draw_spider();
	}
	

	set_material_tiger();
	if(flag_texture_mapping==1) glUniform1i(loc_texture, TEXTURE_ID_TIGER);
	else
		glUniform1i(loc_texture, TEXTURE_ID_RAINBOW);
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-400.0f, 0.0f, 400.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(30.0f, 30.0f, 30.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, 135.0f * TO_RADIAN, glm::vec3(0.0f, 1.0f, .0f));
	if (r_flag == 1) ModelViewMatrix = glm::rotate(ModelViewMatrix, (timestamp_scene % 360) * TO_RADIAN, glm::vec3(.0f, 1.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glm::vec4 position_bike = ModelViewMatrix * glm::vec4(0.0f, 2.0f, 2.0f, 1.0f);
	glUniform4fv(loc_light[4].position, 1, &position_bike[0]);
	glUniform4fv(loc_light[4].ambient_color, 1, light[4].ambient_color);
	glUniform4fv(loc_light[4].diffuse_color, 1, light[4].diffuse_color);
	glUniform4fv(loc_light[4].specular_color, 1, light[4].specular_color);
	glm::vec3 direction_bike = glm::mat3(ModelViewMatrix) * glm::vec3(0.0f, -1.0f, 5.0f);
	glUniform3fv(loc_light[4].spot_direction, 1, &direction_bike[0]);
	glUniform1f(loc_light[4].spot_cutoff_angle, light[4].spot_cutoff_angle);
	glUniform1f(loc_light[4].spot_exponent, light[4].spot_exponent);

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_bike();

	set_material_tiger();
	if (flag_texture_mapping == 1) glUniform1i(loc_texture, TEXTURE_ID_TIGER);
	else
		glUniform1i(loc_texture, TEXTURE_ID_RAINBOW);
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(400.0f, 0.0f, -400.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(30.0f, 30.0f, 30.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, -45.0f * TO_RADIAN, glm::vec3(0.0f, 1.0f, .0f));
	if (r_flag == 1) ModelViewMatrix = glm::rotate(ModelViewMatrix, (timestamp_scene % 360) * TO_RADIAN, glm::vec3(.0f, 1.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glm::vec4 position_bike2 = ModelViewMatrix * glm::vec4(0.0f, 2.0f, 2.0f, 1.0f);
	glUniform4fv(loc_light[5].position, 1, &position_bike2[0]);
	glUniform4fv(loc_light[5].ambient_color, 1, light[5].ambient_color);
	glUniform4fv(loc_light[5].diffuse_color, 1, light[5].diffuse_color);
	glUniform4fv(loc_light[5].specular_color, 1, light[5].specular_color);
	glm::vec3 direction_bike2 = glm::mat3(ModelViewMatrix) * glm::vec3(0.0f, -1.0f, 5.0f);
	glUniform3fv(loc_light[5].spot_direction, 1, &direction_bike2[0]);
	glUniform1f(loc_light[5].spot_cutoff_angle, light[5].spot_cutoff_angle);
	glUniform1f(loc_light[5].spot_exponent, light[5].spot_exponent);

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_bike();

	set_material_tiger();
	if(flag_texture_mapping==1) glUniform1i(loc_texture, TEXTURE_ID_TIGER);
	else 
		glUniform1i(loc_texture, TEXTURE_ID_RAINBOW);
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(400.0f, 0.0f, 400.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(5.0f,5.0f, 5.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, 225.0f * TO_RADIAN, glm::vec3(0.0f, 1.0f, 0.0f));
	if (r_flag == 1) ModelViewMatrix = glm::rotate(ModelViewMatrix, (timestamp_scene % 360) * TO_RADIAN, glm::vec3(.0f, 1.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glm::vec4 position_bus = ModelViewMatrix * glm::vec4(0.0f, 10.0f, 2.0f, 1.0f);
	glUniform4fv(loc_light[6].position, 1, &position_bus[0]);
	glUniform4fv(loc_light[6].ambient_color, 1, light[6].ambient_color);
	glUniform4fv(loc_light[6].diffuse_color, 1, light[6].diffuse_color);
	glUniform4fv(loc_light[6].specular_color, 1, light[6].specular_color);
	glm::vec3 direction_bus = glm::mat3(ModelViewMatrix) * glm::vec3(0.0f, -1.0f, 10.0f);
	glUniform3fv(loc_light[6].spot_direction, 1, &direction_bus[0]);
	glUniform1f(loc_light[6].spot_cutoff_angle, light[6].spot_cutoff_angle);
	glUniform1f(loc_light[6].spot_exponent, light[6].spot_exponent);


	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_bus();

	set_material_tiger();
	if (flag_texture_mapping == 1) glUniform1i(loc_texture, TEXTURE_ID_TIGER);
	else
		glUniform1i(loc_texture, TEXTURE_ID_RAINBOW);
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(-400.0f, 0.0f, -400.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(5.0f, 5.0f, 5.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, 45.0f * TO_RADIAN, glm::vec3(0.0f, 1.0f, .0f));
	if (r_flag == 1) ModelViewMatrix = glm::rotate(ModelViewMatrix, (timestamp_scene % 360) * TO_RADIAN, glm::vec3(.0f, 1.0f, 0.0f));
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glm::vec4 position_bus2 = ModelViewMatrix * glm::vec4(0.0f, 10.0f, 2.0f, 1.0f);
	glUniform4fv(loc_light[7].position, 1, &position_bus2[0]);
	glUniform4fv(loc_light[7].ambient_color, 1, light[7].ambient_color);
	glUniform4fv(loc_light[7].diffuse_color, 1, light[7].diffuse_color);
	glUniform4fv(loc_light[7].specular_color, 1, light[7].specular_color);
	glm::vec3 direction_bus2 = glm::mat3(ModelViewMatrix) * glm::vec3(0.0f, -1.0f, 10.0f);
	glUniform3fv(loc_light[7].spot_direction, 1, &direction_bus2[0]);
	glUniform1f(loc_light[7].spot_cutoff_angle, light[7].spot_cutoff_angle);
	glUniform1f(loc_light[7].spot_exponent, light[7].spot_exponent);


	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_bus();

	set_material_tank();
	if(flag_texture_mapping==1)
		glUniform1i(loc_texture, TEXTURE_ID_TANK);
	else
		glUniform1i(loc_texture, TEXTURE_ID_RAINBOW);
	ModelViewMatrix = glm::rotate(ViewMatrix, -rotation_angle_tiger, glm::vec3(0.0f, 1.0f, 0.0f));
	ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(350.0f, 0.0f, 100.0f));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, -90.0f*TO_RADIAN, glm::vec3(1.0f, 0.0f, 0.0f));
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(20.0f, 20.0f, 20.0f));
	tank = ModelViewMatrix;
	ModelViewProjectionMatrix = ProjectionMatrix * ModelViewMatrix;
	ModelViewMatrixInvTrans = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glm::vec4 position_MC = ModelViewMatrix * glm::vec4(0.0f, 10.0f, 1.0f, 1.0f);
	glUniform4fv(loc_light[3].position, 1, &position_MC[0]);
	glUniform4fv(loc_light[3].ambient_color, 1, light[3].ambient_color);
	glUniform4fv(loc_light[3].diffuse_color, 1, light[3].diffuse_color);
	glUniform4fv(loc_light[3].specular_color, 1, light[3].specular_color);
	glm::vec3 direction_MC = glm::mat3(ModelViewMatrix) * glm::vec3(0.0f, -1.0f, 0.0f);
	glUniform3fv(loc_light[3].spot_direction, 1, &direction_MC[0]);
	glUniform1f(loc_light[3].spot_cutoff_angle, 10.0f);
	glUniform1f(loc_light[3].spot_exponent, 5.0f);

	glUniformMatrix4fv(loc_ModelViewProjectionMatrix_TXPS, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	glUniformMatrix4fv(loc_ModelViewMatrix_TXPS, 1, GL_FALSE, &ModelViewMatrix[0][0]);
	glUniformMatrix3fv(loc_ModelViewMatrixInvTrans_TXPS, 1, GL_FALSE, &ModelViewMatrixInvTrans[0][0]);
	draw_tank();


	glUseProgram(0);

	glutSwapBuffers();
}

void timer_scene(int value) {
	timestamp_scene = (timestamp_scene + 1) % UINT_MAX;
	cur_frame_tiger = timestamp_scene % N_TIGER_FRAMES;
	cur_frame_ben = timestamp_scene % N_BEN_FRAMES;
	cur_frame_wolf= timestamp_scene % N_WOLF_FRAMES;
	cur_frame_spider = timestamp_scene % N_SPIDER_FRAMES;
	rotation_angle_tiger = (timestamp_scene % 360)*TO_RADIAN;
	glutPostRedisplay();
	if (flag_tiger_animation)
		glutTimerFunc(10, timer_scene, 0);
}


void keyboard(unsigned char key, int x, int y) {
	static int flag_cull_face = 0;
	static int PRP_distance_level = 3;
	static int flag_blind_effect = 0;

	glm::vec4 position_EC;
	glm::vec3 direction_EC;

	if ((key >= '0') && (key <= '0' + NUMBER_OF_LIGHT_SUPPORTED - 1)) {
		int light_ID = (int)(key - '0');

		glUseProgram(h_ShaderProgram_TXPS);
		light[light_ID].light_on = 1 - light[light_ID].light_on;
		glUniform1i(loc_light[light_ID].light_on, light[light_ID].light_on);
		glUseProgram(0);

		glutPostRedisplay();
		return;
	}

	switch (key) {
	case 'a': // toggle the animation effect.
		flag_tiger_animation = 1 - flag_tiger_animation;
		if (flag_tiger_animation) {
			glutTimerFunc(100, timer_scene, 0);
			fprintf(stdout, "^^^ Animation mode ON.\n");
		}
		else
			fprintf(stdout, "^^^ Animation mode OFF.\n");
		break;
	case 'f':
		flag_fog = 1 - flag_fog;
		glUseProgram(h_ShaderProgram_TXPS);
		glUniform1i(loc_flag_fog, flag_fog);
		glUseProgram(0);
		glutPostRedisplay();
		break;
	case 't':
		flag_texture_mapping = 1 - flag_texture_mapping;
		glutPostRedisplay();
		break;
	case 'c':
		flag_cull_face = (flag_cull_face + 1) % 3;
		switch (flag_cull_face) {
		case 0:
			glDisable(GL_CULL_FACE);
			glutPostRedisplay();
			break;
		case 1: // cull back faces;
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
			glutPostRedisplay();
			break;
		case 2: // cull front faces;
			glCullFace(GL_FRONT);
			glEnable(GL_CULL_FACE);
			glutPostRedisplay();
			break;
		}
		break;
	case 'n':
		PRP_distance_level--;
		//PRP_distance_level = PRP_distance_level % 6;
		if (PRP_distance_level == 0) PRP_distance_level = 1;
		fprintf(stdout, "^^^ Distance level = %d.\n", PRP_distance_level);

		camera.pos[0] = 250.0 * PRP_distance_level; camera.pos[1] = 150.0 * PRP_distance_level;  camera.pos[2] = 250.0 * PRP_distance_level;
		set_ViewMatrix_from_camera_frame();

		glUseProgram(h_ShaderProgram_TXPS);
		// Must update the light 1's geometry in EC.
		position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
			light[1].position[2], light[1].position[3]);
		glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
		direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0],
			light[1].spot_direction[1], light[1].spot_direction[2]);
		glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
		glUseProgram(0);
		glutPostRedisplay();
		break;
	case 'd':
		PRP_distance_level++;
		//PRP_distance_level = PRP_distance_level % 6;
		if (PRP_distance_level > 6) PRP_distance_level = 6;
		fprintf(stdout, "^^^ Distance level = %d.\n", PRP_distance_level);

		camera.pos[0] = 250.0 * PRP_distance_level; camera.pos[1] = 150.0 * PRP_distance_level;  camera.pos[2] = 250.0 * PRP_distance_level;
		set_ViewMatrix_from_camera_frame();

		glUseProgram(h_ShaderProgram_TXPS);
		// Must update the light 1's geometry in EC.
		position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
			light[1].position[2], light[1].position[3]);
		glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
		direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0],
			light[1].spot_direction[1], light[1].spot_direction[2]);
		glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
		glUseProgram(0);
		glutPostRedisplay();
		break;
	case 'p':
		flag_polygon_fill = 1 - flag_polygon_fill;
		if (flag_polygon_fill)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 's':
		flag_draw_screen = 1 - flag_draw_screen;
		glutPostRedisplay();
		break;
	case 'e':
		if (flag_draw_screen) {
			flag_screen_effect = 1 - flag_screen_effect;
			glutPostRedisplay();
		}
		break;
#define SCEEN_MAX_FREQUENCY 50.0f
	case 'l':
		if (flag_draw_screen) {
			screen_frequency += 1.0f;
			if (screen_frequency > SCEEN_MAX_FREQUENCY)
				screen_frequency = SCEEN_MAX_FREQUENCY;
			glUseProgram(h_ShaderProgram_TXPS);
			glUniform1f(loc_screen_frequency, screen_frequency);
			glUseProgram(0);
			glutPostRedisplay();
		}
		break;
#define SCEEN_MIN_FREQUENCY 1.0f
	case 'v':
		if (flag_draw_screen) {
			screen_frequency -= 1.0f;
			if (screen_frequency < SCEEN_MIN_FREQUENCY)
				screen_frequency = SCEEN_MIN_FREQUENCY;
			glUseProgram(h_ShaderProgram_TXPS);
			glUniform1f(loc_screen_frequency, screen_frequency);
			glUseProgram(0);
			glutPostRedisplay();
		}
		break;
	case 'w':
		flag_blind_effect = 1 - flag_blind_effect;
		glUseProgram(h_ShaderProgram_TXPS);
		glUniform1i(loc_blind_effect, flag_blind_effect);
		glUseProgram(0);
		glutPostRedisplay();
		break;
	case 'x':
		flag_translation_axis = X_AXIS;
		break;
	case 'y':
		flag_translation_axis = Y_AXIS;
		break;
	case 'z':
		flag_translation_axis = Z_AXIS;
		break;
	case 'r':
		r_flag = 1 - r_flag;
		glUseProgram(h_ShaderProgram_TXPS);
		for (int light_ID = 4; light_ID < 8; light_ID++) {
			light[light_ID].light_on = 1 - light[light_ID].light_on;
			glUniform1i(loc_light[light_ID].light_on, light[light_ID].light_on);
		}
		glUseProgram(0);
		glutPostRedisplay();
		break;
	case 'q':
		q_flag = 1 - q_flag;
		if (q_flag == 1) {
			glUseProgram(h_ShaderProgram_TXPS);
			loc_ModelViewProjectionMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewProjectionMatrix");
			loc_ModelViewMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrix");
			loc_ModelViewMatrixInvTrans_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrixInvTrans");

			loc_global_ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_global_ambient_color");
			loc_light[0].position = glGetUniformLocation(h_ShaderProgram_TXPS, "u_light[0].position");
			loc_light[0].ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_light[0].ambient_color");
			loc_light[0].diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_light[0].diffuse_color");
			loc_light[0].specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_light[0].specular_color");

			loc_material.ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.ambient_color");
			loc_material.diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.diffuse_color");
			loc_material.specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_color");
			loc_material.emissive_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.emissive_color");
			loc_material.specular_exponent = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_exponent");

		}
		else
		{
			glUseProgram(h_ShaderProgram_GS);
			loc_ModelViewProjectionMatrix_GS = glGetUniformLocation(h_ShaderProgram_GS, "u_ModelViewProjectionMatrix");
			loc_ModelViewMatrix_GS = glGetUniformLocation(h_ShaderProgram_GS, "u_ModelViewMatrix");
			loc_ModelViewMatrixInvTrans_GS = glGetUniformLocation(h_ShaderProgram_GS, "u_ModelViewMatrixInvTrans");

			loc_global_ambient_color = glGetUniformLocation(h_ShaderProgram_GS, "u_global_ambient_color");
			loc_light[0].position = glGetUniformLocation(h_ShaderProgram_GS, "u_light[0].position");
			loc_light[0].ambient_color = glGetUniformLocation(h_ShaderProgram_GS, "u_light[0].ambient_color");
			loc_light[0].diffuse_color = glGetUniformLocation(h_ShaderProgram_GS, "u_light[0].diffuse_color");
			loc_light[0].specular_color = glGetUniformLocation(h_ShaderProgram_GS, "u_light[0].specular_color");

			loc_material.ambient_color = glGetUniformLocation(h_ShaderProgram_GS, "u_material.ambient_color");
			loc_material.diffuse_color = glGetUniformLocation(h_ShaderProgram_GS, "u_material.diffuse_color");
			loc_material.specular_color = glGetUniformLocation(h_ShaderProgram_GS, "u_material.specular_color");
			loc_material.emissive_color = glGetUniformLocation(h_ShaderProgram_GS, "u_material.emissive_color");
			loc_material.specular_exponent = glGetUniformLocation(h_ShaderProgram_GS, "u_material.specular_exponent");

		}
		glUniform1i(loc_light[0].light_on, light[0].light_on);
		glUniform4fv(loc_light[0].position, 1, light[0].position);
		glUniform4fv(loc_light[0].ambient_color, 1, light[0].ambient_color);
		glUniform4fv(loc_light[0].diffuse_color, 1, light[0].diffuse_color);
		glUniform4fv(loc_light[0].specular_color, 1, light[0].specular_color);
		glUseProgram(0);

		glutPostRedisplay();
		break;
	case 27: // ESC key
		glutLeaveMainLoop(); // Incur destuction callback for cleanups
		break;
	}
}

void motion(int x, int y) {
	if (!camera.move) return;

	renew_cam_position(prevy - y);
	renew_cam_orientation_rotation_around_v_axis(prevx - x);

	prevx = x; prevy = y;

	set_ViewMatrix_from_camera_frame();
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	glm::vec4 position_EC;
	glm::vec3 direction_EC;

	glUseProgram(h_ShaderProgram_TXPS);
	// Must update the light 1's geometry in EC.
	position_EC = ViewMatrix * glm::vec4(light[1].position[0], light[1].position[1],
		light[1].position[2], light[1].position[3]);
	glUniform4fv(loc_light[1].position, 1, &position_EC[0]);
	direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[1].spot_direction[0],
		light[1].spot_direction[1], light[1].spot_direction[2]);
	glUniform3fv(loc_light[1].spot_direction, 1, &direction_EC[0]);
	glUseProgram(0);

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON)) {
		if (state == GLUT_DOWN) {
			camera.move = 1;
			prevx = x; prevy = y;
		}
		else if (state == GLUT_UP) camera.move = 0;
	}
}


void reshape(int width, int height) {
	float aspect_ratio;

	glViewport(0, 0, width, height);
	
	camera.aspect_ratio = (float) width / height;
	aspect_ratio = (float)width / height;
	ProjectionMatrix = glm::perspective(camera.fovy*TO_RADIAN, camera.aspect_ratio, camera.near_c, camera.far_c);
	
	//ProjectionMatrix = glm::perspective(45.0f*TO_RADIAN, aspect_ratio, 100.0f, 20000.0f);

	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	glutPostRedisplay();
}

void cleanup(void) {
	glDeleteVertexArrays(1, &axes_VAO); 
	glDeleteBuffers(1, &axes_VBO);

	glDeleteVertexArrays(1, &rectangle_VAO);
	glDeleteBuffers(1, &rectangle_VBO);

	glDeleteVertexArrays(1, &tiger_VAO);
	glDeleteBuffers(1, &tiger_VBO);

	glDeleteTextures(N_TEXTURES_USED, texture_names);
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutTimerFunc(100, timer_scene, 0);
	glutCloseFunc(cleanup);
}


void prepare_shader_program(void) {
	int i;
	char string[256];
	
	ShaderInfo shader_info_simple[3] = {
		{ GL_VERTEX_SHADER, "Shaders/simple.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
		{ GL_NONE, NULL }
	};
	ShaderInfo shader_info_TXPS[3] = {
		{ GL_VERTEX_SHADER, "Shaders/Phong_Tx.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/Phong_Tx.frag" },
		{ GL_NONE, NULL }
	};
	ShaderInfo shader_info_GS[3] = {
	{ GL_VERTEX_SHADER, "Shaders/Gouraud.vert" },
	{ GL_FRAGMENT_SHADER, "Shaders/Gouraud.frag" },
	{ GL_NONE, NULL }
	};
	
	h_ShaderProgram_simple = LoadShaders(shader_info_simple);
	loc_primitive_color = glGetUniformLocation(h_ShaderProgram_simple, "u_primitive_color");
	loc_ModelViewProjectionMatrix_simple = glGetUniformLocation(h_ShaderProgram_simple, "u_ModelViewProjectionMatrix");
	
	h_ShaderProgram_TXPS = LoadShaders(shader_info_TXPS);
	loc_ModelViewProjectionMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewProjectionMatrix");
	loc_ModelViewMatrix_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrix");
	loc_ModelViewMatrixInvTrans_TXPS = glGetUniformLocation(h_ShaderProgram_TXPS, "u_ModelViewMatrixInvTrans");

	loc_global_ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_global_ambient_color");
	for (i = 0; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		sprintf(string, "u_light[%d].light_on", i);
		loc_light[i].light_on = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].position", i);
		loc_light[i].position = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].ambient_color", i);
		loc_light[i].ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].diffuse_color", i);
		loc_light[i].diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].specular_color", i);
		loc_light[i].specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_direction", i);
		loc_light[i].spot_direction = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_exponent", i);
		loc_light[i].spot_exponent = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].spot_cutoff_angle", i);
		loc_light[i].spot_cutoff_angle = glGetUniformLocation(h_ShaderProgram_TXPS, string);
		sprintf(string, "u_light[%d].light_attenuation_factors", i);
		loc_light[i].light_attenuation_factors = glGetUniformLocation(h_ShaderProgram_TXPS, string);
	}

	loc_material.ambient_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.ambient_color");
	loc_material.diffuse_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.diffuse_color");
	loc_material.specular_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_color");
	loc_material.emissive_color = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.emissive_color");
	loc_material.specular_exponent = glGetUniformLocation(h_ShaderProgram_TXPS, "u_material.specular_exponent");

	loc_texture = glGetUniformLocation(h_ShaderProgram_TXPS, "u_base_texture");

	loc_flag_texture_mapping = glGetUniformLocation(h_ShaderProgram_TXPS, "u_flag_texture_mapping");
	loc_flag_fog = glGetUniformLocation(h_ShaderProgram_TXPS, "u_flag_fog");

	loc_screen_effect = glGetUniformLocation(h_ShaderProgram_TXPS, "screen_effect");
	loc_screen_frequency = glGetUniformLocation(h_ShaderProgram_TXPS, "screen_frequency");
	loc_screen_width = glGetUniformLocation(h_ShaderProgram_TXPS, "screen_width");

	loc_blind_effect = glGetUniformLocation(h_ShaderProgram_TXPS, "u_blind_effect");


	h_ShaderProgram_GS = LoadShaders(shader_info_GS);
	loc_ModelViewProjectionMatrix_GS = glGetUniformLocation(h_ShaderProgram_GS, "u_ModelViewProjectionMatrix");
	loc_ModelViewMatrix_GS = glGetUniformLocation(h_ShaderProgram_GS, "u_ModelViewMatrix");
	loc_ModelViewMatrixInvTrans_GS = glGetUniformLocation(h_ShaderProgram_GS, "u_ModelViewMatrixInvTrans");
}

void initialize_lights_and_material(void) { // follow OpenGL conventions for initialization
	int i;

	glUseProgram(h_ShaderProgram_TXPS);

	glUniform4f(loc_global_ambient_color, 0.115f, 0.115f, 0.115f, 1.0f);
	for (i = 0; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		glUniform1i(loc_light[i].light_on, 0); // turn off all lights initially
		glUniform4f(loc_light[i].position, 0.0f, 0.0f, 1.0f, 0.0f);
		glUniform4f(loc_light[i].ambient_color, 0.0f, 0.0f, 0.0f, 1.0f);
		if (i == 0) {
			glUniform4f(loc_light[i].diffuse_color, 1.0f, 1.0f, 1.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			glUniform4f(loc_light[i].diffuse_color, 0.0f, 0.0f, 0.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		glUniform3f(loc_light[i].spot_direction, 0.0f, 0.0f, -1.0f);
		glUniform1f(loc_light[i].spot_exponent, 0.0f); // [0.0, 128.0]
		glUniform1f(loc_light[i].spot_cutoff_angle, 180.0f); // [0.0, 90.0] or 180.0 (180.0 for no spot light effect)
		glUniform4f(loc_light[i].light_attenuation_factors, 1.0f, 0.0f, 0.0f, 0.0f); // .w != 0.0f for no ligth attenuation
	}

	glUniform4f(loc_material.ambient_color, 0.2f, 0.2f, 0.2f, 1.0f);
	glUniform4f(loc_material.diffuse_color, 0.8f, 0.8f, 0.8f, 1.0f);
	glUniform4f(loc_material.specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform4f(loc_material.emissive_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform1f(loc_material.specular_exponent, 0.0f); // [0.0, 128.0]

	glUseProgram(0);
}

void initialize_flags(void) {
	flag_tiger_animation = 1;
	flag_polygon_fill = 1;
	flag_texture_mapping = 1;
	flag_fog = 0;

	glUseProgram(h_ShaderProgram_TXPS);
	glUniform1i(loc_flag_fog, flag_fog);
	glUniform1i(loc_flag_texture_mapping, flag_texture_mapping);
	glUseProgram(0);
}

void initialize_OpenGL(void) {

	glEnable(GL_MULTISAMPLE);


  	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//ViewMatrix = glm::lookAt(PRP_distance_scale[0] * glm::vec3(500.0f, 300.0f, 500.0f),
	//	glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ViewMatrix = glm::lookAt(4.0f/6.0f * glm::vec3(500.0f, 600.0f, 500.0f),
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	ProjectionMatrix = glm::mat4(1.0f);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	flag_translation_axis = Z_AXIS;

	initialize_lights_and_material();
	initialize_flags();

	glGenTextures(N_TEXTURES_USED, texture_names);
}

void set_up_scene_lights(void) {
	// point_light_EC: use light 0
	light[0].light_on = 1;
	light[0].position[0] = 200.0f; light[0].position[1] = 500.0f; 	// point light position in EC
	light[0].position[2] = 200.0f; light[0].position[3] = 1.0f;

	light[0].ambient_color[0] = 0.13f; light[0].ambient_color[1] = 0.13f;
	light[0].ambient_color[2] = 0.13f; light[0].ambient_color[3] = 1.0f;

	light[0].diffuse_color[0] = 0.5f; light[0].diffuse_color[1] = 0.5f;
	light[0].diffuse_color[2] = 0.5f; light[0].diffuse_color[3] = 1.5f;

	light[0].specular_color[0] = 0.8f; light[0].specular_color[1] = 0.8f;
	light[0].specular_color[2] = 0.8f; light[0].specular_color[3] = 1.0f;

	light[0].spot_direction[0] = 0.0f; light[0].spot_direction[1] = -1.0f; // spot light direction in WC
	light[0].spot_direction[2] = 0.0f;
	light[0].spot_cutoff_angle = 20.0f;
	light[0].spot_exponent = 8.0f;

	light[1].light_on = 1;
	light[1].position[0] = -200.0f; light[1].position[1] = 400.0f; 	// point light position in EC
	light[1].position[2] = -200.0f; light[1].position[3] = 1.0f;

	light[1].ambient_color[0] = 0.13f; light[1].ambient_color[1] = 0.13f;
	light[1].ambient_color[2] = 0.13f; light[1].ambient_color[3] = 1.0f;

	light[1].diffuse_color[0] = 2.5f; light[1].diffuse_color[1] = 0.5f;
	light[1].diffuse_color[2] = 0.5f; light[1].diffuse_color[3] = 1.5f;

	light[1].specular_color[0] = 0.8f; light[1].specular_color[1] = 0.8f;
	light[1].specular_color[2] = 0.8f; light[1].specular_color[3] = 1.0f;

	light[1].spot_direction[0] = 1.0f; light[1].spot_direction[1] = -5.0f; // spot light direction in WC
	light[1].spot_direction[2] = 1.0f;
	light[1].spot_cutoff_angle = 15.0f;
	light[1].spot_exponent = 5.0f;


	light[2].light_on = 0;
	light[2].position[0] = 0.0f; light[2].position[1] = 500.0f;
	light[2].position[2] = 0.0f; light[2].position[3] = 1.0f;

	light[2].ambient_color[0] = 0.15f; light[2].ambient_color[1] = 0.15f;
	light[2].ambient_color[2] = 0.15f; light[2].ambient_color[3] = 1.0f;

	light[2].diffuse_color[0] = 1.572f; light[2].diffuse_color[1] = 1.0f;
	light[2].diffuse_color[2] = 1.2f; light[2].diffuse_color[3] = 1.0f;

	light[2].specular_color[0] = 0.7f; light[2].specular_color[1] = 0.7f;
	light[2].specular_color[2] = 0.7f; light[2].specular_color[3] = 1.0f;

	light[2].spot_direction[0] = 1.0f; light[2].spot_direction[1] = -5.0f;
	light[2].spot_direction[2] = 1.0f;
	light[2].spot_cutoff_angle = 20.0f;
	light[2].spot_exponent = 8.0f;

	// spot_light_WC: use light 3

	light[3].light_on = 0;

	light[3].ambient_color[0] = 0.15f; light[3].ambient_color[1] = 0.25f;
	light[3].ambient_color[2] = 0.25f; light[3].ambient_color[3] = 1.0f;

	light[3].diffuse_color[0] = 1.0f; light[3].diffuse_color[1] = 2.0f;
	light[3].diffuse_color[2] = 2.0f; light[3].diffuse_color[3] = 1.0f;

	light[3].specular_color[0] = 0.7f; light[3].specular_color[1] = 0.7f;
	light[3].specular_color[2] = 0.7f; light[3].specular_color[3] = 1.0f;

	////////////////

	light[4].light_on = 0;

	light[4].ambient_color[0] = 0.152f; light[4].ambient_color[1] = 0.152f;
	light[4].ambient_color[2] = 0.152f; light[4].ambient_color[3] = 1.0f;

	light[4].diffuse_color[0] = 1.0f; light[4].diffuse_color[1] = 2.0f;
	light[4].diffuse_color[2] = 1.0f; light[4].diffuse_color[3] = 1.0f;


	light[4].specular_color[0] = 0.772f; light[4].specular_color[1] = 0.772f;
	light[4].specular_color[2] = 0.772f; light[4].specular_color[3] = 1.0f;

	light[4].spot_direction[0] = 0.0f; light[4].spot_direction[1] = -1.0f; // spot light direction in WC
	light[4].spot_direction[2] = 0.0f;
	light[4].spot_cutoff_angle = 20.0f;
	light[4].spot_exponent = 5.0f;


	light[5].light_on = 0;

	light[5].ambient_color[0] = 0.152f; light[5].ambient_color[1] = 0.152f;
	light[5].ambient_color[2] = 0.152f; light[5].ambient_color[3] = 1.0f;

	light[5].diffuse_color[0] = 2.0f; light[5].diffuse_color[1] = 1.0f;
	light[5].diffuse_color[2] = 1.0f; light[5].diffuse_color[3] = 1.0f;

	light[5].specular_color[0] = 0.772f; light[5].specular_color[1] = 0.772f;
	light[5].specular_color[2] = 0.772f; light[5].specular_color[3] = 1.0f;

	light[5].spot_cutoff_angle = 20.0f;
	light[5].spot_exponent = 5.0f;

	light[6].light_on = 0;

	light[6].ambient_color[0] = 0.152f; light[6].ambient_color[1] = 0.152f;
	light[6].ambient_color[2] = 0.152f; light[6].ambient_color[3] = 1.0f;

	light[6].diffuse_color[0] = 2.0f; light[6].diffuse_color[1] = 1.0f;
	light[6].diffuse_color[2] = 2.0f; light[6].diffuse_color[3] = 1.0f;

	light[6].specular_color[0] = 0.772f; light[6].specular_color[1] = 0.772f;
	light[6].specular_color[2] = 0.772f; light[6].specular_color[3] = 1.0f;

	light[6].spot_cutoff_angle = 10.0f;
	light[6].spot_exponent = 5.0f;

	light[7].light_on = 0;

	light[7].ambient_color[0] = 0.152f; light[7].ambient_color[1] = 0.152f;
	light[7].ambient_color[2] = 0.152f; light[7].ambient_color[3] = 1.0f;

	light[7].diffuse_color[0] = 2.0f; light[7].diffuse_color[1] = 2.0f;
	light[7].diffuse_color[2] = 1.0f; light[7].diffuse_color[3] = 1.0f;

	light[7].specular_color[0] = 0.772f; light[7].specular_color[1] = 0.772f;
	light[7].specular_color[2] = 0.772f; light[7].specular_color[3] = 1.0f;

	light[7].spot_cutoff_angle = 10.0f;
	light[7].spot_exponent = 5.0f;



	glUseProgram(h_ShaderProgram_TXPS);
	glUniform1i(loc_light[0].light_on, light[0].light_on);
	glUniform4fv(loc_light[0].position, 1, light[0].position);
	glUniform4fv(loc_light[0].ambient_color, 1, light[0].ambient_color);
	glUniform4fv(loc_light[0].diffuse_color, 1, light[0].diffuse_color);
	glUniform4fv(loc_light[0].specular_color, 1, light[0].specular_color);

	glUniform1i(loc_light[1].light_on, light[1].light_on);
	
	//glm::vec4 position_WC = camera_view * glm::vec4(200.0f, 300.0f, 200.0f, 1.0f);
	//glUniform4fv(loc_light[1].position, 1, &position_WC[0]);
	glUniform4fv(loc_light[1].ambient_color, 1, light[1].ambient_color);
	glUniform4fv(loc_light[1].diffuse_color, 1, light[1].diffuse_color);
	glUniform4fv(loc_light[1].specular_color, 1, light[1].specular_color);
	//glm::vec3 direction_WC = glm::mat3(camera_view) * glm::vec3(0.0f, -1.0f, 0.0f);
	//glUniform3fv(loc_light[1].spot_direction, 1, &direction_WC[0]);
	glUniform1f(loc_light[1].spot_cutoff_angle, light[1].spot_cutoff_angle);
	glUniform1f(loc_light[1].spot_exponent, light[1].spot_exponent);



	glUniform1i(loc_light[2].light_on, light[2].light_on);
	// need to supply position in EC for shading
	glm::vec4 position_EC = ViewMatrix * glm::vec4(light[2].position[0], light[2].position[1],
												light[2].position[2], light[2].position[3]);
	glUniform4fv(loc_light[2].position, 1, &position_EC[0]); 
	glUniform4fv(loc_light[2].ambient_color, 1, light[2].ambient_color);
	glUniform4fv(loc_light[2].diffuse_color, 1, light[2].diffuse_color);
	glUniform4fv(loc_light[2].specular_color, 1, light[2].specular_color);
	// need to supply direction in EC for shading in this example shader
	// note that the viewing transform is a rigid body transform
	// thus transpose(inverse(mat3(ViewMatrix)) = mat3(ViewMatrix)
	glm::vec3 direction_EC = glm::mat3(ViewMatrix) * glm::vec3(light[2].spot_direction[0], light[2].spot_direction[1], 
																light[2].spot_direction[2]);
	glUniform3fv(loc_light[2].spot_direction, 1, &direction_EC[0]); 
	glUniform1f(loc_light[2].spot_cutoff_angle, light[2].spot_cutoff_angle);
	glUniform1f(loc_light[2].spot_exponent, light[2].spot_exponent);

	////
	glUniform1i(loc_light[3].light_on, light[3].light_on);

	glUniform1i(loc_light[4].light_on, light[4].light_on);
	glUniform1i(loc_light[5].light_on, light[5].light_on);
	glUniform1i(loc_light[6].light_on, light[6].light_on);
	glUniform1i(loc_light[7].light_on, light[7].light_on);

	glUseProgram(0);
}

void prepare_scene(void) {
	prepare_axes();
	prepare_floor();
	prepare_tiger();
	prepare_ben();
	prepare_wolf();
	prepare_spider();
	prepare_dragon();
	prepare_optimus();
	prepare_cow();
	prepare_bus();
	prepare_bike();
	prepare_godzilla();
	prepare_ironman();
	prepare_tank();
	set_up_scene_lights();
	initialize_screen();
}

void initialize_renderer(void) {
	register_callbacks();
	prepare_shader_program();
	initialize_OpenGL();
	prepare_scene();
	initialize_camera();
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

#define N_MESSAGE_LINES 1
void main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 3D Objects";
	char messages[N_MESSAGE_LINES][256] = { "    - Keys used: '0', '1', 'a', 't', 'f', 'c', 'd', 'y', 'u', 'i', 'o', 'ESC'"  };

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 800);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}