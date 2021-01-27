#pragma once
GLfloat axes[4][2];
GLfloat axes_color[3] = { 0.0f, 0.0f, 0.0f };
GLuint VBO_axes, VAO_axes;

void prepare_axes(void) { // Draw axes in their MC.
	axes[0][0] = -win_width / 2.5f; axes[0][1] = 0.0f;
	axes[1][0] = win_width / 2.5f; axes[1][1] = 0.0f;
	axes[2][0] = 0.0f; axes[2][1] = -win_height / 2.5f;
	axes[3][0] = 0.0f; axes[3][1] = win_height / 2.5f;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_axes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_axes);
	glBindVertexArray(VAO_axes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void update_axes(void) {
	axes[0][0] = -win_width / 2.5f; axes[1][0] = win_width / 2.5f;
	axes[2][1] = -win_height / 2.5f;
	axes[3][1] = win_height / 2.5f;

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_axes(void) {
	glUniform3fv(loc_primitive_color, 1, axes_color);
	glBindVertexArray(VAO_axes);
	glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0);
}

#define AIRPLANE_BIG_WING 0
#define AIRPLANE_SMALL_WING 1
#define AIRPLANE_BODY 2
#define AIRPLANE_BACK 3
#define AIRPLANE_SIDEWINDER1 4
#define AIRPLANE_SIDEWINDER2 5
#define AIRPLANE_CENTER 6
GLfloat big_wing[6][2] = { { 0.0, 0.0 }, { -20.0, 15.0 }, { -20.0, 20.0 }, { 0.0, 23.0 }, { 20.0, 20.0 }, { 20.0, 15.0 } };
GLfloat small_wing[6][2] = { { 0.0, -18.0 }, { -11.0, -12.0 }, { -12.0, -7.0 }, { 0.0, -10.0 }, { 12.0, -7.0 }, { 11.0, -12.0 } };
GLfloat body[5][2] = { { 0.0, -25.0 }, { -6.0, 0.0 }, { -6.0, 22.0 }, { 6.0, 22.0 }, { 6.0, 0.0 } };
GLfloat back[5][2] = { { 0.0, 25.0 }, { -7.0, 24.0 }, { -7.0, 21.0 }, { 7.0, 21.0 }, { 7.0, 24.0 } };
GLfloat sidewinder1[5][2] = { { -20.0, 10.0 }, { -18.0, 3.0 }, { -16.0, 10.0 }, { -18.0, 20.0 }, { -20.0, 20.0 } };
GLfloat sidewinder2[5][2] = { { 20.0, 10.0 }, { 18.0, 3.0 }, { 16.0, 10.0 }, { 18.0, 20.0 }, { 20.0, 20.0 } };
GLfloat center[1][2] = { { 0.0, 0.0 } };
GLfloat airplane_color[7][3] = {
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // big_wing
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // small_wing
	{ 111 / 255.0f,  85 / 255.0f, 157 / 255.0f },  // body
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // back
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder1
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder2
	{ 111 / 255.0f,  85 / 255.0f,  157 / 255.0f }   // center
};

GLuint VBO_airplane, VAO_airplane;

#define AIRPLANE_ROTATION_RADIUS 200.0f
float airplane_s_factor = 1.0f;
float airplane2_s_factor = 1.0f;

void prepare_airplane() {
	GLsizeiptr buffer_size = sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2) + sizeof(center);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(big_wing), big_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing), sizeof(small_wing), small_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing), sizeof(body), body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body), sizeof(back), back);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back),
		sizeof(sidewinder1), sidewinder1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1), sizeof(sidewinder2), sidewinder2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2), sizeof(center), center);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_airplane);
	glBindVertexArray(VAO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_airplane() { // Draw airplane in its MC.
	glBindVertexArray(VAO_airplane);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BIG_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SMALL_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BACK]);
	glDrawArrays(GL_TRIANGLE_FAN, 17, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER1]);
	glDrawArrays(GL_TRIANGLE_FAN, 22, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER2]);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_CENTER]);
	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 32, 1);
	glPointSize(1.0);
	glBindVertexArray(0);
}


//airplane2
#define AIRPLANE2_ROTATION_RADIUS 180.0f
GLfloat airplane_color2[7][3] = {
	{ 255 / 255.0f, 180 / 255.0f, 180 / 255.0f },  // big_wing
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // small_wing
	{ 245 / 255.0f,  100 / 255.0f, 100 / 255.0f },  // body
	{ 255 / 255.0f, 180 / 255.0f, 180 / 255.0f },  // back
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder1
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder2
	{ 245 / 255.0f,   100 / 255.0f,   100 / 255.0f }   // center
};

void draw_airplane2() { // Draw airplane in its MC.
	glBindVertexArray(VAO_airplane);

	glUniform3fv(loc_primitive_color, 1, airplane_color2[AIRPLANE_BIG_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color2[AIRPLANE_SMALL_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color2[AIRPLANE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color2[AIRPLANE_BACK]);
	glDrawArrays(GL_TRIANGLE_FAN, 17, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color2[AIRPLANE_SIDEWINDER1]);
	glDrawArrays(GL_TRIANGLE_FAN, 22, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color2[AIRPLANE_SIDEWINDER2]);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color2[AIRPLANE_CENTER]);
	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 32, 1);
	glPointSize(1.0);
	glBindVertexArray(0);
}



//house
#define HOUSE_ROOF 0
#define HOUSE_BODY 1
#define HOUSE_CHIMNEY 2
#define HOUSE_DOOR 3
#define HOUSE_WINDOW 4

GLfloat roof[3][2] = { { -12.0, 0.0 },{ 0.0, 12.0 },{ 12.0, 0.0 } };
GLfloat house_body[4][2] = { { -12.0, -14.0 },{ -12.0, 0.0 },{ 12.0, 0.0 },{ 12.0, -14.0 } };
GLfloat chimney[4][2] = { { 6.0, 6.0 },{ 6.0, 14.0 },{ 10.0, 14.0 },{ 10.0, 2.0 } };
GLfloat door[4][2] = { { -8.0, -14.0 },{ -8.0, -8.0 },{ -4.0, -8.0 },{ -4.0, -14.0 } };
GLfloat window[4][2] = { { 4.0, -6.0 },{ 4.0, -2.0 },{ 8.0, -2.0 },{ 8.0, -6.0 } };

GLfloat house_color[5][3] = {
	{ 200 / 255.0f, 39 / 255.0f, 42 / 255.0f },
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 233 / 255.0f, 113 / 255.0f, 23 / 255.0f },
	{ 44 / 255.0f, 180 / 255.0f, 49 / 255.0f }
};

GLuint VBO_house, VAO_house;
void prepare_house() {
	GLsizeiptr buffer_size = sizeof(roof) + sizeof(house_body) + sizeof(chimney) + sizeof(door)
		+ sizeof(window);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_house);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_house);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(roof), roof);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof), sizeof(house_body), house_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body), sizeof(chimney), chimney);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body) + sizeof(chimney), sizeof(door), door);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body) + sizeof(chimney) + sizeof(door),
		sizeof(window), window);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_house);
	glBindVertexArray(VAO_house);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_house);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_house() {
	glBindVertexArray(VAO_house);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_ROOF]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 3, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_CHIMNEY]);
	glDrawArrays(GL_TRIANGLE_FAN, 7, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_DOOR]);
	glDrawArrays(GL_TRIANGLE_FAN, 11, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

	glBindVertexArray(0);
}


//draw cocktail
#define COCKTAIL_NECK 0
#define COCKTAIL_LIQUID 1
#define COCKTAIL_REMAIN 2
#define COCKTAIL_STRAW 3
#define COCKTAIL_DECO 4

GLfloat neck[6][2] = { { -6.0, -12.0 },{ -6.0, -11.0 },{ -1.0, 0.0 },{ 1.0, 0.0 },{ 6.0, -11.0 },{ 6.0, -12.0 } };
GLfloat liquid[6][2] = { { -1.0, 0.0 },{ -9.0, 4.0 },{ -12.0, 7.0 },{ 12.0, 7.0 },{ 9.0, 4.0 },{ 1.0, 0.0 } };
GLfloat remain[4][2] = { { -12.0, 7.0 },{ -12.0, 10.0 },{ 12.0, 10.0 },{ 12.0, 7.0 } };
GLfloat straw[4][2] = { { 7.0, 7.0 },{ 12.0, 12.0 },{ 14.0, 12.0 },{ 9.0, 7.0 } };
GLfloat deco[8][2] = { { 12.0, 12.0 },{ 10.0, 14.0 },{ 10.0, 16.0 },{ 12.0, 18.0 },{ 14.0, 18.0 },{ 16.0, 16.0 },{ 16.0, 14.0 },{ 14.0, 12.0 } };

GLfloat cocktail_color[5][3] = {
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 0 / 255.0f, 63 / 255.0f, 122 / 255.0f },
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 191 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 218 / 255.0f, 165 / 255.0f, 32 / 255.0f }
};

GLuint VBO_cocktail, VAO_cocktail;
void prepare_cocktail() {
	GLsizeiptr buffer_size = sizeof(neck) + sizeof(liquid) + sizeof(remain) + sizeof(straw)
		+ sizeof(deco);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_cocktail);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cocktail);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(neck), neck);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck), sizeof(liquid), liquid);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck) + sizeof(liquid), sizeof(remain), remain);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck) + sizeof(liquid) + sizeof(remain), sizeof(straw), straw);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(neck) + sizeof(liquid) + sizeof(remain) + sizeof(straw),
		sizeof(deco), deco);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_cocktail);
	glBindVertexArray(VAO_cocktail);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cocktail);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_cocktail() {
	glBindVertexArray(VAO_cocktail);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_NECK]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_LIQUID]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_REMAIN]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_STRAW]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, cocktail_color[COCKTAIL_DECO]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 8);

	glBindVertexArray(0);
}


//cocktail2
GLfloat cocktail_color2[5][3] = {
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 255 / 255.0f, 165 / 255.0f, 0 / 255.0f },
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 191 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 218 / 255.0f, 165 / 255.0f, 32 / 255.0f }
};

void draw_cocktail2() {
	glBindVertexArray(VAO_cocktail);

	glUniform3fv(loc_primitive_color, 1, cocktail_color2[COCKTAIL_NECK]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, cocktail_color2[COCKTAIL_LIQUID]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, cocktail_color2[COCKTAIL_REMAIN]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cocktail_color2[COCKTAIL_STRAW]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, cocktail_color2[COCKTAIL_DECO]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 8);

	glBindVertexArray(0);
}

//shirt
#define SHIRT_LEFT_BODY 0
#define SHIRT_RIGHT_BODY 1
#define SHIRT_LEFT_COLLAR 2
#define SHIRT_RIGHT_COLLAR 3
#define SHIRT_FRONT_POCKET 4
#define SHIRT_BUTTON1 5
#define SHIRT_BUTTON2 6
#define SHIRT_BUTTON3 7
#define SHIRT_BUTTON4 8
GLfloat left_body[6][2] = { { 0.0, -9.0 },{ -8.0, -9.0 },{ -11.0, 8.0 },{ -6.0, 10.0 },{ -3.0, 7.0 },{ 0.0, 9.0 } };
GLfloat right_body[6][2] = { { 0.0, -9.0 },{ 0.0, 9.0 },{ 3.0, 7.0 },{ 6.0, 10.0 },{ 11.0, 8.0 },{ 8.0, -9.0 } };
GLfloat left_collar[4][2] = { { 0.0, 9.0 },{ -3.0, 7.0 },{ -6.0, 10.0 },{ -4.0, 11.0 } };
GLfloat right_collar[4][2] = { { 0.0, 9.0 },{ 4.0, 11.0 },{ 6.0, 10.0 },{ 3.0, 7.0 } };
GLfloat front_pocket[6][2] = { { 5.0, 0.0 },{ 4.0, 1.0 },{ 4.0, 3.0 },{ 7.0, 3.0 },{ 7.0, 1.0 },{ 6.0, 0.0 } };
GLfloat button1[3][2] = { { -1.0, 6.0 },{ 1.0, 6.0 },{ 0.0, 5.0 } };
GLfloat button2[3][2] = { { -1.0, 3.0 },{ 1.0, 3.0 },{ 0.0, 2.0 } };
GLfloat button3[3][2] = { { -1.0, 0.0 },{ 1.0, 0.0 },{ 0.0, -1.0 } };
GLfloat button4[3][2] = { { -1.0, -3.0 },{ 1.0, -3.0 },{ 0.0, -4.0 } };

GLfloat shirt_color[9][3] = {
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f },
	{ 206 / 255.0f, 173 / 255.0f, 184 / 255.0f }
};

GLuint VBO_shirt, VAO_shirt;
void prepare_shirt() {
	GLsizeiptr buffer_size = sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1) + sizeof(button2) + sizeof(button3) + sizeof(button4);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_shirt);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_shirt);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(left_body), left_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body), sizeof(right_body), right_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body), sizeof(left_collar), left_collar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar), sizeof(right_collar), right_collar);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar),
		sizeof(front_pocket), front_pocket);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket), sizeof(button1), button1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1), sizeof(button2), button2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1) + sizeof(button2), sizeof(button3), button3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(left_body) + sizeof(right_body) + sizeof(left_collar) + sizeof(right_collar)
		+ sizeof(front_pocket) + sizeof(button1) + sizeof(button2) + sizeof(button3), sizeof(button4), button4);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_shirt);
	glBindVertexArray(VAO_shirt);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_shirt);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_shirt() {
	glBindVertexArray(VAO_shirt);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_LEFT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_RIGHT_COLLAR]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_FRONT_POCKET]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 6);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON1]);
	glDrawArrays(GL_TRIANGLE_FAN, 26, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON2]);
	glDrawArrays(GL_TRIANGLE_FAN, 29, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON3]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 3);

	glUniform3fv(loc_primitive_color, 1, shirt_color[SHIRT_BUTTON4]);
	glDrawArrays(GL_TRIANGLE_FAN, 35, 3);
	glBindVertexArray(0);
}


// hat
#define HAT_LEAF 0
#define HAT_BODY 1
#define HAT_STRIP 2
#define HAT_BOTTOM 3

GLfloat hat_leaf[4][2] = { { 3.0, 20.0 },{ 3.0, 28.0 },{ 9.0, 32.0 },{ 9.0, 24.0 } };
GLfloat hat_body[4][2] = { { -19.5, 2.0 },{ 19.5, 2.0 },{ 15.0, 20.0 },{ -15.0, 20.0 } };
GLfloat hat_strip[4][2] = { { -20.0, 0.0 },{ 20.0, 0.0 },{ 19.5, 2.0 },{ -19.5, 2.0 } };
GLfloat hat_bottom[4][2] = { { 25.0, 0.0 },{ -25.0, 0.0 },{ -25.0, -4.0 },{ 25.0, -4.0 } };

GLfloat hat_color[4][3] = {
	{ 167 / 255.0f, 255 / 255.0f, 55 / 255.0f },
{ 255 / 255.0f, 144 / 255.0f, 32 / 255.0f },
{ 255 / 255.0f, 40 / 255.0f, 33 / 255.0f },
{ 255 / 255.0f, 144 / 255.0f, 32 / 255.0f }
};

GLuint VBO_hat, VAO_hat;

void prepare_hat() {
	GLsizeiptr buffer_size = sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip) + sizeof(hat_bottom);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(hat_leaf), hat_leaf);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf), sizeof(hat_body), hat_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body), sizeof(hat_strip), hat_strip);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip), sizeof(hat_bottom), hat_bottom);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_hat);
	glBindVertexArray(VAO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_hat() {
	glBindVertexArray(VAO_hat);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_LEAF]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_STRIP]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glBindVertexArray(0);
}

// cake
#define CAKE_FIRE 0
#define CAKE_CANDLE 1
#define CAKE_BODY 2
#define CAKE_BOTTOM 3
#define CAKE_DECORATE 4

GLfloat cake_fire[4][2] = { { -0.5, 14.0 },{ -0.5, 13.0 },{ 0.5, 13.0 },{ 0.5, 14.0 } };
GLfloat cake_candle[4][2] = { { -1.0, 8.0 } ,{ -1.0, 13.0 },{ 1.0, 13.0 },{ 1.0, 8.0 } };
GLfloat cake_body[4][2] = { { 8.0, 5.0 },{ -8.0, 5.0 } ,{ -8.0, 8.0 },{ 8.0, 8.0 } };
GLfloat cake_bottom[4][2] = { { -10.0, 1.0 },{ -10.0, 5.0 },{ 10.0, 5.0 },{ 10.0, 1.0 } };
GLfloat cake_decorate[4][2] = { { -10.0, 0.0 },{ -10.0, 1.0 },{ 10.0, 1.0 },{ 10.0, 0.0 } };

GLfloat cake_color[5][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 204 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 102 / 255.0f, 51 / 255.0f, 0 / 255.0f }
};

GLuint VBO_cake, VAO_cake;

void prepare_cake() {
	int size = sizeof(cake_fire);
	GLsizeiptr buffer_size = sizeof(cake_fire) * 5;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, size, cake_fire);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, cake_candle);
	glBufferSubData(GL_ARRAY_BUFFER, size * 2, size, cake_body);
	glBufferSubData(GL_ARRAY_BUFFER, size * 3, size, cake_bottom);
	glBufferSubData(GL_ARRAY_BUFFER, size * 4, size, cake_decorate);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_cake);
	glBindVertexArray(VAO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_cake() {
	glBindVertexArray(VAO_cake);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_FIRE]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_CANDLE]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_DECORATE]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glBindVertexArray(0);
}

//cake2
GLfloat cake2_color[5][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 204 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
{ 102 / 255.0f, 51 / 255.0f, 0 / 255.0f }
};
void draw_cake2() {
	glBindVertexArray(VAO_cake);

	glUniform3fv(loc_primitive_color, 1, cake2_color[CAKE_FIRE]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, cake2_color[CAKE_CANDLE]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, cake2_color[CAKE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, cake2_color[CAKE_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cake2_color[CAKE_DECORATE]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glBindVertexArray(0);
}

// sword

#define SWORD_BODY 0
#define SWORD_BODY2 1
#define SWORD_HEAD 2
#define SWORD_HEAD2 3
#define SWORD_IN 4
#define SWORD_DOWN 5
#define SWORD_BODY_IN 6

GLfloat sword_body[4][2] = { { -6.0, 0.0 },{ -6.0, -4.0 },{ 6.0, -4.0 },{ 6.0, 0.0 } };
GLfloat sword_body2[4][2] = { { -2.0, -4.0 },{ -2.0, -6.0 } ,{ 2.0, -6.0 },{ 2.0, -4.0 } };
GLfloat sword_head[4][2] = { { -2.0, 0.0 },{ -2.0, 16.0 } ,{ 2.0, 16.0 },{ 2.0, 0.0 } };
GLfloat sword_head2[3][2] = { { -2.0, 16.0 },{ 0.0, 19.46 } ,{ 2.0, 16.0 } };
GLfloat sword_in[4][2] = { { -0.3, 0.7 },{ -0.3, 15.3 } ,{ 0.3, 15.3 },{ 0.3, 0.7 } };
GLfloat sword_down[4][2] = { { -2.0, -6.0 } ,{ 2.0, -6.0 },{ 4.0, -8.0 },{ -4.0, -8.0 } };
GLfloat sword_body_in[4][2] = { { 0.0, -1.0 } ,{ 1.0, -2.732 },{ 0.0, -4.464 },{ -1.0, -2.732 } };

GLfloat sword_color[7][3] = {
	{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f }
};

GLuint VBO_sword, VAO_sword;

void prepare_sword() {
	GLsizeiptr buffer_size = sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down) + sizeof(sword_body_in);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sword_body), sword_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body), sizeof(sword_body2), sword_body2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2), sizeof(sword_head), sword_head);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head), sizeof(sword_head2), sword_head2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2), sizeof(sword_in), sword_in);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in), sizeof(sword_down), sword_down);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down), sizeof(sword_body_in), sword_body_in);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_sword);
	glBindVertexArray(VAO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_sword() {
	glBindVertexArray(VAO_sword);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY2]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 3);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_DOWN]);
	glDrawArrays(GL_TRIANGLE_FAN, 19, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 23, 4);

	glBindVertexArray(0);
}
//draw car2
#define CAR2_BODY 0
#define CAR2_FRONT_WINDOW 1
#define CAR2_BACK_WINDOW 2
#define CAR2_FRONT_WHEEL 3
#define CAR2_BACK_WHEEL 4
#define CAR2_LIGHT1 5
#define CAR2_LIGHT2 6

GLfloat car2_body[8][2] = { { -18.0, -7.0 },{ -18.0, 0.0 },{ -13.0, 0.0 },{ -10.0, 8.0 },{ 10.0, 8.0 },{ 13.0, 0.0 },{ 18.0, 0.0 },{ 18.0, -7.0 } };
GLfloat car2_front_window[4][2] = { { -10.0, 0.0 },{ -8.0, 6.0 },{ -2.0, 6.0 },{ -2.0, 0.0 } };
GLfloat car2_back_window[4][2] = { { 0.0, 0.0 },{ 0.0, 6.0 },{ 8.0, 6.0 },{ 10.0, 0.0 } };
GLfloat car2_front_wheel[8][2] = { { -11.0, -11.0 },{ -13.0, -8.0 },{ -13.0, -7.0 },{ -11.0, -4.0 },{ -7.0, -4.0 },{ -5.0, -7.0 },{ -5.0, -8.0 },{ -7.0, -11.0 } };
GLfloat car2_back_wheel[8][2] = { { 7.0, -11.0 },{ 5.0, -8.0 },{ 5.0, -7.0 },{ 7.0, -4.0 },{ 11.0, -4.0 },{ 13.0, -7.0 },{ 13.0, -8.0 },{ 11.0, -11.0 } };
GLfloat car2_light1[3][2] = { { -18.0, -1.0 },{ -17.0, -2.0 },{ -18.0, -3.0 } };
GLfloat car2_light2[3][2] = { { -18.0, -4.0 },{ -17.0, -5.0 },{ -18.0, -6.0 } };

GLfloat car2_color[7][3] = {
	{ 100 / 255.0f, 141 / 255.0f, 159 / 255.0f },
	{ 235 / 255.0f, 219 / 255.0f, 208 / 255.0f },
	{ 235 / 255.0f, 219 / 255.0f, 208 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f }
};

GLuint VBO_car2, VAO_car2;
void prepare_car2() {
	GLsizeiptr buffer_size = sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel) + sizeof(car2_light1) + sizeof(car2_light2);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_car2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car2);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car2_body), car2_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body), sizeof(car2_front_window), car2_front_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window), sizeof(car2_back_window), car2_back_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window), sizeof(car2_front_wheel), car2_front_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel),
		sizeof(car2_back_wheel), car2_back_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel), sizeof(car2_light1), car2_light1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel) + sizeof(car2_light1), sizeof(car2_light2), car2_light2);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_car2);
	glBindVertexArray(VAO_car2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car2);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_car2() {
	glBindVertexArray(VAO_car2);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_FRONT_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BACK_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_FRONT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BACK_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_LIGHT1]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 3);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_LIGHT2]);
	glDrawArrays(GL_TRIANGLE_FAN, 35, 3);

	glBindVertexArray(0);
}

//car
#define CAR_BODY 0
#define CAR_FRAME 1
#define CAR_WINDOW 2
#define CAR_LEFT_LIGHT 3
#define CAR_RIGHT_LIGHT 4
#define CAR_LEFT_WHEEL 5
#define CAR_RIGHT_WHEEL 6

GLfloat car_body[4][2] = { { -16.0, -8.0 },{ -16.0, 0.0 },{ 16.0, 0.0 },{ 16.0, -8.0 } };
GLfloat car_frame[4][2] = { { -10.0, 0.0 },{ -10.0, 10.0 },{ 10.0, 10.0 },{ 10.0, 0.0 } };
GLfloat car_window[4][2] = { { -8.0, 0.0 },{ -8.0, 8.0 },{ 8.0, 8.0 },{ 8.0, 0.0 } };
GLfloat car_left_light[4][2] = { { -9.0, -6.0 },{ -10.0, -5.0 },{ -9.0, -4.0 },{ -8.0, -5.0 } };
GLfloat car_right_light[4][2] = { { 9.0, -6.0 },{ 8.0, -5.0 },{ 9.0, -4.0 },{ 10.0, -5.0 } };
GLfloat car_left_wheel[4][2] = { { -10.0, -12.0 },{ -10.0, -8.0 },{ -6.0, -8.0 },{ -6.0, -12.0 } };
GLfloat car_right_wheel[4][2] = { { 6.0, -12.0 },{ 6.0, -8.0 },{ 10.0, -8.0 },{ 10.0, -12.0 } };

GLfloat car_color[7][3] = {
	{ 0 / 255.0f, 149 / 255.0f, 159 / 255.0f },
	{ 0 / 255.0f, 149 / 255.0f, 159 / 255.0f },
	{ 216 / 255.0f, 208 / 255.0f, 174 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 21 / 255.0f, 30 / 255.0f, 26 / 255.0f },
	{ 21 / 255.0f, 30 / 255.0f, 26 / 255.0f }
};

GLuint VBO_car, VAO_car;
void prepare_car() {
	GLsizeiptr buffer_size = sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light) + sizeof(car_left_wheel) + sizeof(car_right_wheel);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_car);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_body), car_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body), sizeof(car_frame), car_frame);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame), sizeof(car_window), car_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window), sizeof(car_left_light), car_left_light);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light),
		sizeof(car_right_light), car_right_light);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light), sizeof(car_left_wheel), car_left_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light) + sizeof(car_left_wheel), sizeof(car_right_wheel), car_right_wheel);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_car);
	glBindVertexArray(VAO_car);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_car() {
	glBindVertexArray(VAO_car);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_FRAME]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_LEFT_LIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_RIGHT_LIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_LEFT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_RIGHT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);

	glBindVertexArray(0);
}



//tree
GLfloat tree_1[4][2] = { {-2.0, 12.0}, {0.0, 18.0}, {0.0, 18.0}, {2.0, 12.0} };
GLfloat tree_2[4][2] = { {-4.0, 6.0}, {-1.0, 12.0}, {1.0, 12.0}, {4.0, 6.0} };
GLfloat tree_3[4][2] = { {-6.0, 0.0}, {-3.0, 6.0},  {3.0, 6.0}, {6.0, 0.0} };
GLfloat tree_4[4][2] = { {-2.0, 0.0}, {-2.0, -6.0}, {2.0, -6.0}, {2.0, 0.0} };

GLfloat tree_color[4][3] = {
	{ 0 / 255.0f, 128 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 128 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 128 / 255.0f, 0 / 255.0f },
	{ 111 / 255.0f, 79 / 255.0f, 40 / 255.0f }
};

GLuint VBO_tree, VAO_tree;

void prepare_tree() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(tree_1)+sizeof(tree_2)+sizeof(tree_3)+sizeof(tree_4);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_tree);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tree_1), tree_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(tree_1), sizeof(tree_2), tree_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(tree_1)+sizeof(tree_2), sizeof(tree_3), tree_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(tree_1)+sizeof(tree_2)+sizeof(tree_3), sizeof(tree_4), tree_4);

	
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_tree);
	glBindVertexArray(VAO_tree);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_tree() {
	glBindVertexArray(VAO_tree);

	glUniform3fv(loc_primitive_color, 1, tree_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, tree_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, tree_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, tree_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glBindVertexArray(0);
}

//tree2
GLfloat tree2_color[4][3] = {
	{ 42 / 255.0f, 111 / 255.0f, 55 / 255.0f },
	{ 26 / 255.0f, 102 / 255.0f, 46 / 255.0f },
	{ 0 / 255.0f, 82 / 255.0f, 33 / 255.0f },
	{ 150 / 255.0f, 75 / 255.0f, 40 / 255.0f }
};

void draw_tree2() {
	glBindVertexArray(VAO_tree);

	glUniform3fv(loc_primitive_color, 1, tree2_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, tree2_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, tree2_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, tree2_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glBindVertexArray(0);
}


//land
GLfloat land[4][2] = { {-200.0, 200.0}, {-200.0, -200.0}, {200.0, -200.0}, {200.0, 200.0} };


GLfloat land_color[1][3] = {
	{ 65 / 255.0f, 68 / 255.0f, 73 / 255.0f }
};

GLuint VBO_land, VAO_land;

void prepare_land() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(land);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_land);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_land);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(land), land);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(tree_1), sizeof(tree_2), tree_2);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(tree_1) + sizeof(tree_2), sizeof(tree_3), tree_3);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(tree_1) + sizeof(tree_2) + sizeof(tree_3), sizeof(tree_4), tree_4);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_land);
	glBindVertexArray(VAO_land);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_land);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_land() {
	glBindVertexArray(VAO_land);

	glUniform3fv(loc_primitive_color, 1, land_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindVertexArray(0);
}


//building
GLfloat building[4][2] = { {-100.0, 120.0}, {-100.0, -120.0}, {100.0, -120.0}, {100.0, 120.0} };
GLfloat window_1[4][2] = { {-70.0, 90.0}, {-70.0, 60.0}, {-40.0, 60.0}, {-40.0, 90.0} };
GLfloat window_2[4][2] = { {-70.0, 30.0}, {-70.0, 0.0}, {-40.0, 0.0}, {-40.0, 30.0} };
GLfloat window_3[4][2] = { {70.0, 90.0}, {70.0, 60.0}, {40.0, 60.0}, {40.0, 90.0} };
GLfloat window_4[4][2] = { {70.0, 30.0}, {70.0, 0.0}, {40.0, 0.0}, {40.0, 30.0} };
GLfloat window_5[4][2] = { {-70.0, -60.0}, {-70.0, -30.0}, {-40.0, -30.0}, {-40.0, -60.0} };
GLfloat window_6[4][2] = { {70.0, -60.0}, {70.0, -30.0}, {40.0, -30.0}, {40.0, -60.0} };


GLfloat building_color[7][3] = {
	{ 128 / 255.0f, 128 / 255.0f, 128 / 255.0f },
	{ 135 / 255.0f, 206 / 255.0f, 235 / 255.0f },
	{ 135 / 255.0f, 206 / 255.0f, 235 / 255.0f },
	{ 135 / 255.0f, 206 / 255.0f, 235 / 255.0f },
	{ 135 / 255.0f, 206 / 255.0f, 235 / 255.0f },
	{ 135 / 255.0f, 206 / 255.0f, 235 / 255.0f },
	{ 135 / 255.0f, 206 / 255.0f, 235 / 255.0f }
};

GLuint VBO_building, VAO_building;

void prepare_building() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(building) + sizeof(window_1) + sizeof(window_2) + sizeof(window_3) + sizeof(window_4) + sizeof(window_5) + sizeof(window_6);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_building);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_building);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(building), building);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(building), sizeof(window_1), window_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(building) + sizeof(window_1), sizeof(window_2), window_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(building)+sizeof(window_1)+sizeof(window_2), sizeof(window_3), window_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(building) + sizeof(window_1) + sizeof(window_2)+sizeof(window_3), sizeof(window_4), window_4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(building) + sizeof(window_1) + sizeof(window_2) + sizeof(window_3)+sizeof(window_4), sizeof(window_5), window_5);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(building) + sizeof(window_1) + sizeof(window_2) + sizeof(window_3) + sizeof(window_4)+sizeof(window_5), sizeof(window_6), window_6);



	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_building);
	glBindVertexArray(VAO_building);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_building);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_building() {
	glBindVertexArray(VAO_building);

	glUniform3fv(loc_primitive_color, 1, building_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, building_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, building_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, building_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, building_color[4]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, building_color[5]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glUniform3fv(loc_primitive_color, 1, building_color[6]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);


	glBindVertexArray(0);
}


//basket
GLfloat basket_2[4][2] = { {0.0, 15.0}, {-5.0, 10.0}, {0.0, 5.0}, {10.0, 5.0}};
GLfloat basket_3[4][2] = { {0.0, 15.0}, {10.0, 5.0}, {15.0, 10.0}, {10.0, 15.0} };

GLfloat basket_color[2][3] = {
	{ 71 / 255.0f, 57 / 255.0f, 50 / 255.0f },
	{ 71 / 255.0f, 57 / 255.0f, 50 / 255.0f }
};

GLuint VBO_basket, VAO_basket;

void prepare_basket() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(basket_2) + sizeof(basket_3);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_basket);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_basket);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(basket_2), basket_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(basket_2), sizeof(basket_3), basket_3);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_basket);
	glBindVertexArray(VAO_basket);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_basket);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_basket() {
	glBindVertexArray(VAO_basket);

	glUniform3fv(loc_primitive_color, 1, basket_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, basket_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glBindVertexArray(0);
}


//bastet
GLfloat basket_1[4][2] = { {0.0, 5.0}, {0.0, 0.0}, {10.0, 0.0}, {10.0, 5.0} };
GLfloat basket_4[4][2] = { {-5.0, 10.0}, {-5.0, 10.0}, {0.0, 0.0}, {0.0, 5.0} };
GLfloat basket_5[4][2] = { {10.0, 5.0}, {10.0, 5.0}, {10.0, 0.0}, {15.0, 10.0} };

GLfloat basket2_color[3][3] = {
	{ 89 / 255.0f, 71 / 255.0f, 63 / 255.0f },
	{ 111 / 255.0f, 89 / 255.0f, 79 / 255.0f },
	{ 111 / 255.0f, 89 / 255.0f, 79 / 255.0f }
};

GLuint VBO_basket2, VAO_basket2;

void prepare_basket2() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(basket_1) + sizeof(basket_4) + sizeof(basket_5);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_basket2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_basket2);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(basket_1), basket_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(basket_1), sizeof(basket_4), basket_4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(basket_1) + sizeof(basket_4), sizeof(basket_5), basket_5);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_basket2);
	glBindVertexArray(VAO_basket2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_basket2);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_basket2() {
	glBindVertexArray(VAO_basket2);

	glUniform3fv(loc_primitive_color, 1, basket2_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, basket2_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, basket2_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);


	glBindVertexArray(0);
}


//cloud
GLfloat cloud_1[6][2] = { {0.0, 0.0}, {-3.0, -5.0}, {0.0, -10.0}, {5.0, -10.0}, {8.0, -5.0}, {5.0, 0.0} };
GLfloat cloud_2[6][2] = { {8.0, -5.0}, {5.0, 0.0}, {8.0, 5.0}, {13.0, 5.0}, {16.0, 0.0}, {13.0, -5.0 } };
GLfloat cloud_3[6][2] = { {16.0, 0.0}, {13.0, -5.0 }, {16.0, -10.0}, {21.0, -10.0}, {24.0, -5.0}, {21.0, 0.0} };
GLfloat cloud_4[6][2] = { {8.0, -5.0}, {4.0, -10.0}, {6.5, -18.0}, {14.0, -15.0}, {16.0, -10.0}, {13.0, -5.0} };
GLfloat cloud_5[6][2] = { {16.0, -10.0}, {13.0, -15.0}, {16.0, -20.0}, {21.0, -20.0}, {24.0, -15.0}, {21.0, -10.0} };


GLfloat cloud_color[5][3] = {
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f }
};

GLuint VBO_cloud, VAO_cloud;

void prepare_cloud() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(cloud_1) + sizeof(cloud_2) + sizeof(cloud_3) + sizeof(cloud_4)+sizeof(cloud_5);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_cloud);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cloud);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cloud_1), cloud_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cloud_1), sizeof(cloud_2), cloud_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cloud_1) + sizeof(cloud_2), sizeof(cloud_3), cloud_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cloud_1) + sizeof(cloud_2) + sizeof(cloud_3), sizeof(cloud_4), cloud_4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cloud_1) + sizeof(cloud_2) + sizeof(cloud_3)+sizeof(cloud_4),sizeof(cloud_5), cloud_5);



	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_cloud);
	glBindVertexArray(VAO_cloud);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cloud);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_cloud() {
	glBindVertexArray(VAO_cloud);

	glUniform3fv(loc_primitive_color, 1, cloud_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, cloud_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, cloud_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 6);

	glUniform3fv(loc_primitive_color, 1, cloud_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 18, 6);

	glUniform3fv(loc_primitive_color, 1, cloud_color[4]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 6);


	glBindVertexArray(0);
}

//cloud2

GLfloat cloud2_color[5][3] = {
	{ 230 / 255.0f, 243 / 255.0f, 249 / 255.0f },
	{ 230 / 255.0f, 243 / 255.0f, 249 / 255.0f },
	{ 230 / 255.0f, 243 / 255.0f, 249 / 255.0f },
	{ 230 / 255.0f, 243 / 255.0f, 249 / 255.0f },
	{ 230 / 255.0f, 243 / 255.0f, 249 / 255.0f }
};

void draw_cloud2() {
	glBindVertexArray(VAO_cloud);

	glUniform3fv(loc_primitive_color, 1, cloud2_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, cloud2_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, cloud2_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 6);

	glUniform3fv(loc_primitive_color, 1, cloud2_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 18, 6);

	glUniform3fv(loc_primitive_color, 1, cloud2_color[4]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 6);


	glBindVertexArray(0);
}

//cloud3

GLfloat cloud3_color[5][3] = {
	{ 152 / 255.0f, 152 / 255.0f, 152 / 255.0f },
	{ 152 / 255.0f, 152 / 255.0f, 152 / 255.0f },
	{ 152 / 255.0f, 152 / 255.0f, 152 / 255.0f },
	{ 152 / 255.0f, 152 / 255.0f, 152 / 255.0f },
	{ 152 / 255.0f, 152 / 255.0f, 152 / 255.0f }
};

void draw_cloud3() {
	glBindVertexArray(VAO_cloud);

	glUniform3fv(loc_primitive_color, 1, cloud3_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, cloud3_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, cloud3_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 6);

	glUniform3fv(loc_primitive_color, 1, cloud3_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 18, 6);

	glUniform3fv(loc_primitive_color, 1, cloud3_color[4]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 6);


	glBindVertexArray(0);
}


//bird
GLfloat bird_head[6][2] = { {0.0, 0.0}, {-3.0, -5.0}, {0.0, -10.0}, {5.0, -10.0}, {8.0, -5.0}, {5.0, 0.0} };
GLfloat bird_body[6][2] = { {5.0, -10.0}, {8.0, -5.0}, {20.0, -5.0}, {23.0, -10.0}, {20.0, -15.0}, {8.0, -15.0} };
GLfloat bird_wing[6][2] = { {8.0, -10.0}, {12.0, -7.0}, {17.5, -7.0}, { 16.0, -10.0}, {17.5, -13.0}, {12.0, -13.0} };
GLfloat bird_1[3][2] = { {-3.0, -5.0}, {-5.0, -5.0}, {0.0, -10.0} };
GLfloat bird_eye[1][2] = { {0.0, -3.0} };


GLfloat bird_color[5][3] = {
	{ 236 / 255.0f, 230 / 255.0f, 204 / 255.0f },
	{ 212 / 255.0f, 199 / 255.0f, 140 / 255.0f },
	{ 111 / 255.0f, 79 / 255.0f, 40 / 255.0f },
	{ 255 / 255.0f, 212 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f }
};

GLuint VBO_bird, VAO_bird;

void prepare_bird() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(bird_head) + sizeof(bird_body) + sizeof(bird_wing) + sizeof(bird_1) + sizeof(bird_eye);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_bird);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bird);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bird_head), bird_head);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bird_head), sizeof(bird_body), bird_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bird_head) + sizeof(bird_body), sizeof(bird_wing), bird_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bird_head) + sizeof(bird_body) + sizeof(bird_wing), sizeof(bird_1), bird_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(bird_head) + sizeof(bird_body) + sizeof(bird_wing) + sizeof(bird_1), sizeof(bird_eye), bird_eye);



	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_bird);
	glBindVertexArray(VAO_bird);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_bird);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_bird() {
	glBindVertexArray(VAO_bird);

	glUniform3fv(loc_primitive_color, 1, bird_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, bird_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, bird_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 6);

	glUniform3fv(loc_primitive_color, 1, bird_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 18, 3);


	glUniform3fv(loc_primitive_color, 1, bird_color[4]);
	glPointSize(3.0);
	glDrawArrays(GL_POINTS, 21, 1);
	glPointSize(1.0);

	glBindVertexArray(0);
}


//rain
GLfloat rain[4][2] = { {0.0, 0.0 }, {-1.0, -4.0}, {0.0, -5.0}, {1.0, -4.0} };
GLfloat rain2[4][2] = { {0.0, 100.0 }, {-1.0, 96.0}, {0.0, 95.0}, {1.0, 96.0} };
GLfloat rain3[4][2] = { {0.0, 200.0 }, {-1.0, 196.0}, {0.0, 195.0}, {1.0, 196.0} };
GLfloat rain4[4][2] = { {0.0, 300.0 }, {-1.0, 296.0}, {0.0, 295.0}, {1.0, 296.0} };
GLfloat rain5[4][2] = { {0.0, -200.0 }, {-1.0, -206.0}, {0.0, -205.0}, {1.0, -206.0} };
GLfloat rain6[4][2] = { {0.0, -100.0 }, {-1.0, -106.0}, {0.0, -105.0}, {1.0, -106.0} };

GLfloat rain_color[1][3] = {
	{ 245 / 255.0f, 251 / 255.0f, 255 / 255.0f }
};

GLuint VBO_rain, VAO_rain;

void prepare_rain() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(rain)*6;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_rain);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_rain);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(rain), rain);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rain), sizeof(rain2), rain2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rain)*2, sizeof(rain3), rain3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rain)*3, sizeof(rain4), rain4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rain)*4, sizeof(rain5), rain5);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(rain)*5, sizeof(rain6), rain6);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_rain);
	glBindVertexArray(VAO_rain);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_rain);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_rain() {
	glBindVertexArray(VAO_rain);

	glUniform3fv(loc_primitive_color, 1, rain_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glUniform3fv(loc_primitive_color, 1, rain_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glUniform3fv(loc_primitive_color, 1, rain_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glUniform3fv(loc_primitive_color, 1, rain_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glUniform3fv(loc_primitive_color, 1, rain_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glUniform3fv(loc_primitive_color, 1, rain_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
	glBindVertexArray(0);
}


//snow
GLfloat snow[1][2] = { {0.0, 0.0 } };
GLfloat snow2[1][2] = { {0.0, -100.0 } };
GLfloat snow3[1][2] = { {50.0, 100.0 } };
GLfloat snow4[1][2] = { {0.0, -200.0 } };
GLfloat snow5[1][2] = { {0.0, 200.0 } };
GLfloat snow6[1][2] = { {100.0, -300.0 } };
GLfloat snow7[1][2] = { {0.0, 300.0 } };

GLfloat snow_color[1][3] = {
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f }
};

GLuint VBO_snow, VAO_snow;

void prepare_snow() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(snow)*7;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_snow);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_snow);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(snow), snow);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(snow), sizeof(snow2), snow2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(snow)*2, sizeof(snow3), snow3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(snow)*3, sizeof(snow4), snow4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(snow)*4, sizeof(snow5), snow5);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(snow)*5, sizeof(snow6), snow6);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(snow)*6, sizeof(snow7), snow7);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_snow);
	glBindVertexArray(VAO_snow);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_snow);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_snow() {
	glBindVertexArray(VAO_snow);

	glUniform3fv(loc_primitive_color, 1, snow_color[0]);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(1.0);
	glUniform3fv(loc_primitive_color, 1, snow_color[0]);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 1, 1);
	glPointSize(1.0);
	glUniform3fv(loc_primitive_color, 1, snow_color[0]);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 2, 1);
	glPointSize(1.0);
	glUniform3fv(loc_primitive_color, 1, snow_color[0]);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 3, 1);
	glPointSize(1.0);
	glUniform3fv(loc_primitive_color, 1, snow_color[0]);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 4, 1);
	glPointSize(1.0);
	glUniform3fv(loc_primitive_color, 1, snow_color[0]);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 5, 1);
	glPointSize(1.0);
	glUniform3fv(loc_primitive_color, 1, snow_color[0]);
	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 6, 1);
	glPointSize(1.0);

	glBindVertexArray(0);
}




//guage box
GLfloat gauge_box[4][2] = { {0.0, 0.0}, {0.0, -5.0 }, {20.0, -5.0}, {20.0, 0.0} };
GLfloat gauge_box2[4][2] = { {20.0, -1.0 }, {20.0, -4.0}, {21.3, -4.0}, {21.3, -1.0} };


GLfloat gauge_box_color[2][3] = {
	{ 180 / 255.0f, 180 / 255.0f, 180 / 255.0f },
	{ 180 / 255.0f, 180 / 255.0f, 180 / 255.0f }
};

GLuint VBO_gauge_box, VAO_gauge_box;

void prepare_gauge_box() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(gauge_box)+sizeof(gauge_box2);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_gauge_box);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_gauge_box);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(gauge_box), gauge_box);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gauge_box), sizeof(gauge_box2), gauge_box2);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_gauge_box);
	glBindVertexArray(VAO_gauge_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_gauge_box);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_gauge_box() {
	glBindVertexArray(VAO_gauge_box);

	glUniform3fv(loc_primitive_color, 1, gauge_box_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, gauge_box_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glBindVertexArray(0);
}


//gauge
GLfloat gauge[4][2] = { {1.0, -0.8}, {1.0, -4.2}, {3.0, -4.2}, {3.0, -0.8} };


GLfloat gauge_color[1][3] = {
	{ 0 / 255.0f, 0 / 255.0f, 255 / 255.0f }
};

GLuint VBO_gauge, VAO_gauge;

void prepare_gauge() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(gauge);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_gauge);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_gauge);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(gauge), gauge);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_gauge);
	glBindVertexArray(VAO_gauge);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_gauge);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_gauge() {
	glBindVertexArray(VAO_gauge);

	glUniform3fv(loc_primitive_color, 1, gauge_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindVertexArray(0);
}


//level
GLfloat level_box[4][2] = { {-75.0, 45.0}, {-75.0, -15.0}, {325.0, -15.0}, {325.0, 45.0} };
GLfloat L1_1[4][2] = { {20.0, 30.0}, {20.0, 0.0},{25.0, 0.0}, {25.0, 30.0} };
GLfloat L1_2[4][2] = { {25.0, 0.0}, {40.0, 0.0}, {40.0, 5.0}, {25.0, 5.0} };
GLfloat E1_1[4][2] = { {50.0, 30.0}, {50.0, 0.0}, {55.0, 0.0}, {55.0, 30.0} };
GLfloat E1_2[4][2] = { {55.0, 0.0}, {70.0, 0.0}, {70.0, 5.0}, {55.0, 5.0} };
GLfloat E1_3[4][2] = { {55.0, 12.5}, {70.0, 12.5}, {70.0, 17.5}, {55.0, 17.5} };
GLfloat E1_4[4][2] = { {55.0, 25.0}, {70.0, 25.0}, {70.0, 30.0}, {55.0, 30.0} };
GLfloat V_1[4][2] = { {80.0, 30.0}, {87.5, 0.0}, {92.5, 0.0}, {85.0, 30.0} };
GLfloat V_2[4][2] = { {87.5, 0.0}, {95.0, 30.0}, {100.0, 30.0}, {92.5, 0.0} };
GLfloat E2_1[4][2] = { {110.0, 30.0}, {110.0, 0.0}, {115.0, 0.0}, {115.0, 30.0} };
GLfloat E2_2[4][2] = { {115.0, 0.0}, {130.0, 0.0}, {130.0, 5.0}, {115.0, 5.0} };
GLfloat E2_3[4][2] = { {115.0, 12.5}, {130.0, 12.5}, {130.0, 17.5}, {115.0, 17.5} };
GLfloat E2_4[4][2] = { {115.0, 25.0}, {130.0, 25.0}, {130.0, 30.0}, {115.0, 30.0} };
GLfloat L2_1[4][2] = { {140.0, 30.0}, {140.0, 0.0},{145.0, 0.0}, {145.0, 30.0} };
GLfloat L2_2[4][2] = { {145.0, 0.0}, {160.0, 0.0}, {160.0, 5.0}, {145.0, 5.0} };
GLfloat U_1[4][2] = { {190.0, 30.0}, {190.0, 0.0},{195.0, 0.0}, {195.0, 30.0} };
GLfloat U_2[4][2] = { {195.0, 0.0}, {210.0, 0.0}, {210.0, 5.0}, {195.0, 5.0} };
GLfloat U_3[4][2] = { {205.0, 30.0}, {205.0, 0.0}, {210.0, 0.0}, {210.0, 30.0} };
GLfloat P_1[4][2] = { {220.0, 30.0}, {220.0, 0.0}, {225.0, 0.0}, {225.0, 30.0} };
GLfloat P_2[4][2] = { {225.0, 30.0}, {240.0, 30.0}, {235.0, 25.0}, {225.0, 25.0} };
GLfloat P_3[4][2] = { {235.0, 30.0}, {240.0, 30.0}, {240.0, 15.0}, {235.0, 15.0} };
GLfloat P_4[4][2] = { {225.0, 20.0}, {240.0, 20.0}, {235.0, 15.0}, {225.0, 15.0} };


GLfloat level_color[2][3] = {
	{ 240 / 255.0f, 240 / 255.0f, 240 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 255 / 255.0f }
};

GLuint VBO_level, VAO_level;

void prepare_level() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(level_box)*22;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_level);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_level);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(level_box), level_box);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box), sizeof(L1_1), L1_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 2, sizeof(L1_2), L1_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 3,sizeof(E1_1), E1_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 4, sizeof(E2_2), E1_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 5, sizeof(E1_3), E1_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 6, sizeof(E1_4), E1_4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 7, sizeof(V_1), V_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 8, sizeof(V_2), V_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 9 , sizeof(E2_1), E2_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 10 , sizeof(E2_2), E2_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 11 , sizeof(E2_3), E2_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 12 , sizeof(E2_4), E2_4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 13 , sizeof(L2_1), L2_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 14 , sizeof(L2_2), L2_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 15 , sizeof(U_1), U_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 16 , sizeof(U_2), U_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 17 , sizeof(U_3), U_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 18 , sizeof(P_1), P_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 19 , sizeof(P_2), P_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 20 , sizeof(P_3), P_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(level_box) * 21 , sizeof(P_4), P_4);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_level);
	glBindVertexArray(VAO_level);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_level);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_level() {
	glBindVertexArray(VAO_level);

	glUniform3fv(loc_primitive_color, 1, level_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 28, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 36, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 44, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 48, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 52, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 56, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 64, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 68, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 72, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 76, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 80, 4);
	glUniform3fv(loc_primitive_color, 1, level_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 84, 4);


	glBindVertexArray(0);
}


//diamond
GLfloat diamond1[3][2] = { {0.0, 6.0}, {-3.0, 0.0}, {0.0, -2.0} };
GLfloat diamond2[3][2] = { {0.0, 6.0}, {3.0, 0.0}, {0.0, -2.0} };
GLfloat diamond3[3][2] = { {-3.0, 0.0}, {0.0, -6.0}, {0.0, -2.0} };
GLfloat diamond4[3][2] = { {0.0, -2.0}, {0.0, -6.0}, {3.0, 0.0} };

GLfloat diamond_color[4][3] = {
	{ 184 / 255.0f, 211 / 255.0f, 245 / 255.0f },
	{ 204/ 255.0f, 222 / 255.0f, 245 / 255.0f },
	{ 145 / 255.0f, 190 / 255.0f, 245 / 255.0f },
	{ 165 / 255.0f, 201 / 255.0f, 245 / 255.0f }
};

GLuint VBO_diamond, VAO_diamond;

void prepare_diamond() {
	//int size = sizeof(tree_1)+sizeof(tree_2);
	GLsizeiptr buffer_size = sizeof(diamond1) * 4;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_diamond);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_diamond);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(diamond1), diamond1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(diamond1), sizeof(diamond2), diamond2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(diamond1)*2, sizeof(diamond3), diamond3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(diamond1)*3, sizeof(diamond4), diamond4);



	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_diamond);
	glBindVertexArray(VAO_diamond);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_diamond);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_diamond() {
	glBindVertexArray(VAO_diamond);

	glUniform3fv(loc_primitive_color, 1, diamond_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	glUniform3fv(loc_primitive_color, 1, diamond_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 3, 3);

	glUniform3fv(loc_primitive_color, 1, diamond_color[2]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 3);

	glUniform3fv(loc_primitive_color, 1, diamond_color[3]);
	glDrawArrays(GL_TRIANGLE_FAN, 9, 3);
	glBindVertexArray(0);
}



//game over
GLfloat gameover_box[4][2] = { {-100.0, -30.0}, {-100.0, 60.0}, {350.0, 60.0}, {350.0, -30.0} };
GLfloat G1[4][2] = { {0.0, 30.0}, {20.0, 30.0}, {20.0, 25.0}, {0.0, 25.0} };
GLfloat G2[4][2] = { {0.0, 0.0}, {20.0, 0.0}, {20.0, 5.0}, {0.0, 5.0} };
GLfloat G3[4][2] = { {0.0, 25.0}, {5.0, 25.0}, {5.0, 5.0}, {0.0, 5.0} };
GLfloat G4[4][2] = { {15.0, 5.0}, {20.0, 5.0}, {20.0, 12.5}, {15.0, 12.5} };
GLfloat G5[4][2] = { {10.0, 17.5}, {10.0, 12.5}, {20.0, 12.5}, {20.0, 17.5 } };
GLfloat A1[4][2] = { {30.0, 30.0}, {35.0, 30.0}, {35.0, 0.0}, {30.0, 0.0} };
GLfloat A2[4][2] = { {45.0, 30.0}, {50.0, 30.0}, {50.0, 0.0}, {45.0, 0.0} };
GLfloat A3[4][2] = { {30.0, 30.0}, {30.0, 25.0},  {50.0, 25.0}, {50.0, 30.0 } };
GLfloat A4[4][2] = { {30.0, 12.5}, {30.0, 17.5}, {50.0, 17.5}, {50.0, 12.5} };
GLfloat M1[4][2] = { {60.0, 30.0}, {60.0, 0.0}, {65.0, 0.0}, {65.0, 30.0} };
GLfloat M2[4][2] = { {75.0, 30.0}, {75.0, 0.0}, {80.0, 0.0}, {80.0, 30.0} };
GLfloat M3[4][2] = { {60.0, 30.0}, {67.5, 0.0}, {72.5, 0.0}, {65.0, 30.0} };
GLfloat M4[4][2] = { {67.5, 0.0}, {72.5, 0.0}, {80.0, 30.0}, {75.0, 30.0} };
GLfloat E1[4][2] = { {90.0, 0.0}, {90.0, 30.0}, {95.0, 30.0}, {95.0, 0.0} };
GLfloat E2[4][2] = { {90.0, 30.0}, {110.0, 30.0}, {110.0, 25.0}, {90.0, 25.0} };
GLfloat E3[4][2] = { {90.0, 17.5}, {110.0, 17.5}, {110.0, 12.5}, {90.0, 12.5} };
GLfloat E4[4][2] = { {90.0, 5.0}, {110.0, 5.0}, {110.0, 0.0}, {90.0, 0.0} };
GLfloat O1[4][2] = { {140.0, 0.0}, {140.0, 30.0}, {145.0, 30.0}, {145.0, 0.0} };
GLfloat O2[4][2] = { {155.0, 0.0}, {155.0, 30.0}, {160.0, 30.0}, {160.0, 0.0} };
GLfloat O3[4][2] = { {140.0, 30.0}, {160.0, 30.0}, {160.0, 25.0}, {140.0, 25.0} };
GLfloat O4[4][2] = { {140.0, 5.0}, {160.0, 5.0}, {160.0, 0.0}, {140.0, 0.0} };
GLfloat V1[4][2] = { {170.0, 30.0}, {175.0, 30.0}, {182.5, 0.0}, {177.5, 0.0} };
GLfloat V2[4][2] = { {185.0, 30.0}, {190.0, 30.0}, {182.5, 0.0}, {177.5, 0.0} };
GLfloat E12[4][2] = { {200.0, 0.0}, {200.0, 30.0}, {205.0, 30.0}, {205.0, 0.0} };
GLfloat E22[4][2] = { {200.0, 30.0}, {220.0, 30.0}, {220.0, 25.0}, {200.0, 25.0} };
GLfloat E32[4][2] = { {200.0, 17.5}, {220.0, 17.5}, {220.0, 12.5}, {200.0, 12.5} };
GLfloat E42[4][2] = { {200.0, 5.0}, {220.0, 5.0}, {220.0, 0.0}, {200.0, 0.0} };
GLfloat R1[4][2] = { {230.0, 30.0}, {235.0, 30.0}, {235.0, 0.0}, {230.0, 0.0} };
GLfloat R2[4][2] = { {230.0, 30.0}, {250.0, 30.0}, {250.0, 25.0}, {230.0, 25.0} };
GLfloat R3[4][2] = { {230.0, 20.0}, {250.0, 20.0}, {250.0, 15.0}, {230.0, 15.0} };
GLfloat R4[4][2] = { {250.0, 30.0}, {245.0, 30.0}, {245.0, 15.0}, {250.0, 15.0} };
GLfloat R5[4][2] = { {240.0, 15.0}, {245.0, 15.0}, {250.0, 0.0}, {245.0, 0.0} };

GLfloat gameover_color[2][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 255 / 255.0f }
};

GLuint VBO_game, VAO_game;

void prepare_gameover() {
	GLsizeiptr buffer_size = sizeof(gameover_box) * 33;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_game);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_game);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(gameover_box), gameover_box);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box), sizeof(G1), G1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box)*2, sizeof(G2), G2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box)*3, sizeof(G3), G3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box)*4, sizeof(G4), G4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box)*5, sizeof(G5), G5);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 6, sizeof(A1), A1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 7, sizeof(A2), A2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 8, sizeof(A3), A3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 9, sizeof(A4), A4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 10, sizeof(M1), M1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 11, sizeof(M2), M2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 12, sizeof(M3), M3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 13, sizeof(M4), M4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 14, sizeof(E1), E1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 15, sizeof(E2), E2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 16, sizeof(E3), E3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 17, sizeof(E4), E4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 18, sizeof(O1), O1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 19, sizeof(O2), O2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 20, sizeof(O3), O3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 21, sizeof(O4), O4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 22, sizeof(V1), V1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 23, sizeof(V2), V2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 24, sizeof(E12), E12);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 25, sizeof(E22), E22);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 26, sizeof(E32), E32);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 27, sizeof(E42), E42);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 28, sizeof(R1), R1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 29, sizeof(R2), R2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 30, sizeof(R3), R3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 31, sizeof(R4), R4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(gameover_box) * 32, sizeof(R5), R5);


	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_game);
	glBindVertexArray(VAO_game);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_game);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_gameover() {
	glBindVertexArray(VAO_game);

	glUniform3fv(loc_primitive_color, 1, gameover_color[0]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 28, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 36, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 40, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 44, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 48, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 52, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 56, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 64, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 68, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 72, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 76, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 80, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 84, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 88, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 92, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 96, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 100, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 104, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 108, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 112, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 116, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 120, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 124, 4);

	glUniform3fv(loc_primitive_color, 1, gameover_color[1]);
	glDrawArrays(GL_TRIANGLE_FAN, 128, 4);

	glBindVertexArray(0);
}
