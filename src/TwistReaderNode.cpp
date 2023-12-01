/*
  TwistReaderNode.cpp
  ===================
  Implements the TwistReaderNode class
*/
#include "TwistReaderNode.hpp"

MTypeId TwistReaderNode::id(0x00000); //ID 0 [TEST ONLY]
MObject TwistReaderNode::object;
MObject TwistReaderNode::offset;
MObject TwistReaderNode::matrix;
MObject TwistReaderNode::twist;

MStatus TwistReaderNode::compute(const MPlug& plug, MDataBlock& data)
{

	MStatus status;

	if (plug == twist)
	{

		//Get matrix to force node update on transform matrix 
		MDataHandle matrixH = data.inputValue(matrix);
		matrixH.asFloat3();

		MDataHandle objH = data.inputValue(object);
		MString str = objH.asString();
		MSelectionList list;
		list.add(str);
		MDagPath dag;
		list.getDagPath(0, dag);
		MFnTransform mat(dag);
		MQuaternion quat;
		mat.getRotation(quat);
		MDataHandle offH = data.inputValue(offset);
		double* wxyz = offH.asDouble4();
		MQuaternion oQuat(wxyz[1], wxyz[2], wxyz[3], wxyz[0]);

		MVector rAim(1, 0, 0);
		MVector rUp(0, 1, 0);
		MVector rForward(0, 0, 1);

		MVector aim = rAim.rotateBy(quat*oQuat);
		MVector up = rUp.rotateBy(quat*oQuat);
		MVector forward = rForward.rotateBy(quat*oQuat);

		MQuaternion rot = rAim.rotateTo(aim);
		MVector iUp = rUp.rotateBy(rot);
		MVector iForward = rForward.rotateBy(rot);

		MDataHandle twistH = data.outputValue(twist);
		if (!iUp.isEquivalent(up, 0.00001) && !iForward.isEquivalent(forward, 0.00001))
		{
		
			MAngle ang(iUp.angle(up));
			if (MAngle(up.angle(iForward)).asRadians() >= MAngle(up.angle(-iForward)).asRadians())
			{

				twistH.setFloat(-ang.asDegrees());

			}
			else
			{

				twistH.setFloat(ang.asDegrees());

			}
		
		}
		else
		{

			twistH.setFloat(0.0);

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

	//Offset input attribute
	offset = nAttr.create("Offset", "off", MFnNumericData::k4Double, 0, &status);
	status = nAttr.setKeyable(false);
	status = nAttr.setConnectable(false);
	status = addAttribute(offset);

	//Matrix input attribute
	matrix = tAttr.create("Matrix", "mat", MFnData::kMatrix, &status);
	status = tAttr.setKeyable(false);
	status = addAttribute(matrix);

	//Twist output attribute
	twist = nAttr.create("Twist", "tw", MFnNumericData::kFloat, 0, &status);
	status = nAttr.setKeyable(false);
	status = nAttr.setWritable(false);
	status = addAttribute(twist);

	//Affects
	attributeAffects(object, twist);
	attributeAffects(offset, twist);
	attributeAffects(matrix, twist);

	return status;

}

void* TwistReaderNode::creator()
{

	return new TwistReaderNode();

}