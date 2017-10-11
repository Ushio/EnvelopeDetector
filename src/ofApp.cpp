#include "ofApp.h"

static const int kLogCount = 60 * 5;
//--------------------------------------------------------------
void ofApp::setup() {

	_camera.setNearClip(0.1f);
	_camera.setFarClip(100.0f);
	_camera.setDistance(5.0f);

	ofSetFrameRate(60);
	ofSetVerticalSync(false);

	_data_raw.resize(kLogCount, 0.0f);
	_data_filterd.resize(kLogCount, 0.0f);

	//float a[] = {
	//	7.483914270309116e-03,
	//	1.634745733863819e-01,
	//	4.000000000000000e-01,
	//	1.634745733863819e-01,
	//	7.483914270309116e-03,
	//};
	//for (int i = 0; i < 5; ++i) {
	//	printf("%.4f\n", a[i]);
	//}
}
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw() {
	float elapsed = ofGetElapsedTimef();

	float value = 10.0f * (ofNoise(elapsed * 0.9f) * 2.0f - 1.0f) * (ofNoise(elapsed * 40.0f) * 2.0f - 1.0f);
	_data_raw.push_back(value);
	_data_raw.erase(_data_raw.begin());

	// http://dsp.jpn.org/cgi-bin/dfcgi/fwin/mado.cgi
	// ƒtƒBƒ‹ƒ^’· = 25
	// LPF
	// •ûŒ`‘‹
	// ³‹K‰»ŽÕ’fŽü”g” 0.001 [‚È‚ñ‚©’á‚ß‚ª‚¢‚¢‚ç‚µ‚¢]
	
	// ’uŠ·
	// \n
	// ,\n
	float a[] = {
		1.998105574515400e-03 ,
		1.998408084091106e-03 ,
		1.998684312479682e-03 ,
		1.998934253138653e-03 ,
		1.999157900148076e-03 ,
		1.999355248210717e-03 ,
		1.999526292652191e-03 ,
		1.999671029421097e-03 ,
		1.999789455089137e-03 ,
		1.999881566851206e-03 ,
		1.999947362525471e-03 ,
		1.999986840553441e-03 ,
		2.000000000000000e-03 ,
		1.999986840553441e-03 ,
		1.999947362525471e-03 ,
		1.999881566851206e-03 ,
		1.999789455089137e-03 ,
		1.999671029421097e-03 ,
		1.999526292652191e-03 ,
		1.999355248210717e-03 ,
		1.999157900148076e-03 ,
		1.998934253138653e-03 ,
		1.998684312479682e-03 ,
		1.998408084091106e-03 ,
		1.998105574515400e-03
	};

	float s = 0;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
		s += a[i];
	}

	static std::vector<float> fir_data(sizeof(a) / sizeof(a[0]));
	fir_data.insert(fir_data.begin(), value * value);
	fir_data.pop_back();
	
	float lpf = 0.0f;
	for (int i = 0; i < fir_data.size(); ++i) {
		lpf += fir_data[i] * a[i];
	}
	lpf /= s;

	_data_filterd.push_back(std::sqrt(lpf));
	_data_filterd.erase(_data_filterd.begin());

	ofClear(0);
	_camera.begin();
	
	ofPushMatrix();
	ofRotateY(90.0f);
	ofSetColor(64);
	ofDrawGridPlane(1.0f);
	ofPopMatrix();

	ofPushMatrix();
	ofDrawAxis(5);
	ofPopMatrix();

	static ofPolyline line;
	{
		line.clear();

		for (int i = 0; i < _data_raw.size(); ++i) {
			float y = _data_raw[i];
			float x = ofMap(i, 0, _data_raw.size() - 1, -2.5f, 2.5f);
			line.addVertex(x, y);
		}

		ofSetColor(255);
		line.draw();
	}
	{
		line.clear();

		for (int i = 0; i < _data_filterd.size(); ++i) {
			float y = _data_filterd[i];
			float x = ofMap(i, 0, _data_filterd.size() - 1, -2.5f, 2.5f);
			line.addVertex(x, y);
		}

		ofSetColor(255, 128, 0);
		line.draw();
	}

	_camera.end();



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
