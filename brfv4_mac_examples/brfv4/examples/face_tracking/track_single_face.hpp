#ifndef __brf__cpp__BRFCppExample_hpp
#define __brf__cpp__BRFCppExample_hpp

namespace brf {

class BRFCppExample: public BRFBasicCppExample {

public: BRFCppExample() : BRFBasicCppExample()
{
}

public: void initCurrentExample(brf::BRFManager& brfManager, brf::Rectangle& resolution) {

	brf::trace("BRFv4 - basic - face tracking - track single face" + brf::to_string("\n")+
		"Detect and track one face and draw the 68 facial landmarks.");

	// By default everything necessary for a single face tracking app
	// is set up for you in brfManager.init. There is actually no
	// need to configure much more for a jump start.
}

public: void updateCurrentExample(brf::BRFManager& brfManager, brf::DrawingUtils& draw) {

	// In a webcam example imageData is the mirrored webcam video feed.
	// In an image example imageData is the (not mirrored) image content.

	brfManager.update();

	// Drawing the results:

	draw.clear();

	// Face detection results: a rough rectangle used to start the face tracking.

	draw.drawRects(brfManager.getAllDetectedFaces(),    false, 1.0, 0x00a1ff, 0.5);
	draw.drawRects(brfManager.getMergedDetectedFaces(), false, 2.0, 0xffd200, 1.0);

	// Get all faces. The default setup only tracks one face.

	std::vector< std::shared_ptr<brf::BRFFace> >& faces = brfManager.getFaces();

	for(size_t i = 0; i < faces.size(); i++) {

		brf::BRFFace& face = *faces[i];

		if(		face.state == brf::BRFState::FACE_TRACKING_START ||
				face.state == brf::BRFState::FACE_TRACKING) {

			// Face tracking results: 68 facial feature points.

			draw.drawTriangles(	face.vertices, face.triangles, false, 1.0, 0x00a0ff, 0.4);
			draw.drawVertices(	face.vertices, 2.0, false, 0x00a0ff, 0.4);
		}
	}
}

};

}
#endif // __brf__cpp__BRFCppExample_hpp
