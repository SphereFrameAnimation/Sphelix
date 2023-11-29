/*
  TwistReaderNode.cpp
  ===================
  Implements the TwistReaderNode class
*/
#include "TwistReaderNode.hpp"

MTypeId TwistReaderNode::id(0x00000); //ID 0 [TEST ONLY]
MObject TwistReaderNode::object;
MObject TwistReaderNode::matrix;
MObject TwistReaderNode::twist;

MStatus TwistReaderNode::compute(const MPlug& plug, MDataBlock& data)
{

	MStatus status;

	if (plug == twist)
	{

		MDataHandle objH = data.inputValue(object);
		MString str = objH.asString();
		MSelectionList list;
		list.add(str);
		MDagPath dag;
		list.getDagPath(0, dag);
		MFnTransform mat(dag);
		MQuaternion quat;
		mat.getRotation(quat);

		MVector rAim(1, 0, 0);
		MVector rUp(0, 1, 0);
		MVector rForward(0, 0, 1);

		MVector aim = rAim.rotateBy(quat);
		MVector up = rUp.rotateBy(quat);
		MVector forward = rForward.rotateBy(quat);

		MQuaternion rot = rAim.rotateTo(aim);
		MVector iUp = rUp.rotateBy(rot);
		MVector iForward = rForward.rotateBy(rot);

		if (!iUp.isEquivalent(up, 0.001) && !iForward.isEquivalent(forward, 0.001))
		{
		
			MAngle ang(iUp.angle(up));
			MDataHandle twistH = data.outputValue(twist);
			if (MAngle(up.angle(iForward)).asRadians() >= MAngle(up.angle(-iForward)).asRadians())
			{

				twistH.setFloat(ang.asDegrees());

			}
			else
			{

				twistH.setFloat(-ang.asDegrees());

			}
		
		}

	}

	return status;

}

MStatus TwistReaderNode::init()
{

	MStatus status;
	MFnTypedAttribute tAttr;
	MFnNumericAttribute nAttr;

	//Object input attribute
	object = tAttr.create("Object", "obj", MFnData::kString, &status);
	status = tAttr.setKeyable(false);
	status = tAttr.setConnectable(false);
	status = addAttribute(object);

	//Matrix input attribute
	matrix = tAttr.create("m", "m", MFnData::kMatrix, &status);
	status = tAttr.setKeyable(false);
	status = addAttribute(matrix);

	//Twist output attribute
	twist = nAttr.create("Twist", "tw", MFnNumericData::kFloat, 0, &status);
	status = nAttr.setKeyable(false);
	status = nAttr.setWritable(false);
	status = addAttribute(twist);

	//Affects
	attributeAffects(object, twist);
	attributeAffects(matrix, twist);

	return status;

}

void* TwistReaderNode::creator()
{

	return new TwistReaderNode();

}