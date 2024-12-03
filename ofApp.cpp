#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(0.5);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	auto ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->base_mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int base_x = -250; base_x <= 250; base_x += 250) {

		for (int base_y = -250; base_y <= 250; base_y += 250) {

			this->draw_mesh.clear();
			auto seed = ofRandom(1000);

			for (auto v : this->base_mesh.getVertices()) {

				ofColor color;
				color.setHsb(ofMap(v.y, -250, 250, 0, 255), ofMap(v.y, -250, 250, 0, 255), ofMap(v.y, -250, 250, 0, 255));

				for (int i = 0; i < 3; i++) {

					auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec3(seed, v.x * 0.0015, ofGetFrameNum() * 0.002)), 0, 1, -300, 300) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
					auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec3(seed, v.y * 0.0015, ofGetFrameNum() * 0.002)), 0, 1, -300, 300) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec3(seed, v.z * 0.0015, ofGetFrameNum() * 0.002)), 0, 1, -300, 300) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

					auto radius = ofMap(ofNoise(glm::vec4(v * 0.01, ofGetFrameNum() * 0.008)), 0, 1, 50, 100);

					v = glm::normalize(v) * radius;
					v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
				}

				this->draw_mesh.addVertex(glm::vec3(v.x + base_x, v.y + base_y, 0));
				this->draw_mesh.addColor(ofColor(color, 16));
			}

			this->draw_mesh.addIndices(this->base_mesh.getIndices());
			this->draw_mesh.drawWireframe();
		}
	}

	/*
	int start = 10;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}