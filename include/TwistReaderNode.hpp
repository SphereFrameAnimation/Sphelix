/*
  TwistReaderNode.hpp
  ===================
  Header defining the TwistReaderNode class
*/
#ifndef SPHELIX_TWISTREADERNODE
#define SPHELIX_TWISTREADERNODE

#include "maya/MPxNode.h"
#include "maya/MFnTypedAttribute.h"
#include "maya/MFnNumericAttribute.h"

class TwistReaderNode : public MPxNode
{

	public:
		static MTypeId id;
		static MObject object;
		static MObject matrix;
		static MObject twist;
		
		MStatus compute(const MPlug& plug, MDataBlock& dataBlock);
		static void* creator();
		static MStatus init();

};

#endif