#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float R = 250;
	float r = 45;
	int v_span = 1;
	int u_span = 10;

	for (int v = 0; v < 360; v += v_span) {

		auto noise_param = glm::vec2(R * cos(v * DEG_TO_RAD), R * sin(v * DEG_TO_RAD));
		auto u_start = ofMap(ofNoise(noise_param.x * 0.005, noise_param.y * 0.005, ofGetFrameNum() * 0.005), 0, 1, -180, 180);
	
		for (int u = u_start; u < u_start + 360; u += 45) {

			vector<glm::vec3> vertices;
			vertices.push_back(this->make_point(R, r, u, v - v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u + u_span, v - v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u + u_span, v + v_span * 0.5));
			vertices.push_back(this->make_point(R, r, u, v + v_span * 0.5));

			int face_index = face.getNumVertices();
			this->face.addVertices(vertices);

			this->face.addIndex(face_index + 0); face.addIndex(face_index + 1); face.addIndex(face_index + 2);
			this->face.addIndex(face_index + 0); face.addIndex(face_index + 2); face.addIndex(face_index + 3);

			int frame_index = frame.getNumVertices();
			this->frame.addVertices(vertices);

			this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index + 1);
			this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index + 2);
			this->frame.addIndex(frame_index + 2); this->frame.addIndex(frame_index + 3);
			this->frame.addIndex(frame_index + 3); this->frame.addIndex(frame_index + 0);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}