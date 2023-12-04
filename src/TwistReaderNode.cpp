/*
  TwistReaderNode.cpp
  ===================
  Implements the TwistReaderNode class
*/
#include "TwistReaderNode.hpp"

MTypeId TwistReaderNode::id(0x13D5C0, 0x00); //ID 1299904-000
MObject TwistReaderNode::object;
MObject TwistReaderNode::aimVec;
MObject TwistReaderNode::upVec;
MObject TwistReaderNode::fwdVec;
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
		matrixH.asMatrix();

		//Get object orientation
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

		//Rest Vectors
		MDataHandle rAimH = data.inputValue(aimVec);
		float* rAimV = rAimH.asFloat3();
		MVector rAim(rAimV[0], rAimV[1], rAimV[2]);
		MDataHandle rUpH = data.inputValue(upVec);
		float* rUpV = rUpH.asFloat3();
		MVector rUp(rUpV[0], rUpV[1], rUpV[2]);
		MDataHandle rFwdH = data.inputValue(fwdVec);
		float* rFwdV = rFwdH.asFloat3();
		MVector rForward(rFwdV[0], rFwdV[1], rFwdV[2]);

		//Actual Vectors
		MVector aim = rAim.rotateBy(quat*oQuat);
		MVector up = rUp.rotateBy(quat*oQuat);
		MVector forward = rForward.rotateBy(quat*oQuat);

		//Intended Vectors
		MQuaternion rot = rAim.rotateTo(aim);
		MVector iUp = rUp.rotateBy(rot);
		MVector iForward = rForward.rotateBy(rot);

		//Check if the Actual Up and Forward vectors are misaligned to the Intended Up and Forward vectors
		MDataHandle twistH = data.outputValue(twist);
		if (!iUp.isEquivalent(up, 0.00001) && !iForward.isEquivalent(forward, 0.00001))
		{
		
			//Calculate angle between Intended and Actual vectors
			MAngle ang(iUp.angle(up));

			//Check if the Actual up vector is closer to the Intended Forward vector or the negation of the Intended Forward Vector
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

	//Aim Vector input attribute
	aimVec = nAttr.create("Aim Vector", "aim", MFnNumericData::k3Float, 0, &status);
	status = nAttr.setDefault(1.0F, 0.0F, 0.0F);
	status = nAttr.setKeyable(false);
	status = nAttr.setConnectable(false);
	status = addAttribute(aimVec);

	//Up Vector input attribute
	upVec = nAttr.create("Up Vector", "up", MFnNumericData::k3Float, 0, &status);
	status = nAttr.setDefault(0.0F, 1.0F, 0.0F);
	status = nAttr.setKeyable(false);
	status = nAttr.setConnectable(false);
	status = addAttribute(upVec);

	//Forward Vector input attribute
	fwdVec = nAttr.create("Forward Vector", "fwd", MFnNumericData::k3Float, 0, &status);
	status = nAttr.setDefault(0.0F, 0.0F, 1.0F);
	status = nAttr.setKeyable(false);
	status = nAttr.setConnectable(false);
	status = addAttribute(fwdVec);

	//Offset input attribute
	offset = nAttr.create("Offset", "off", MFnNumericData::k4Double, 0, &status);
	status = nAttr.setDefault(1.0, 0.0, 0.0, 0.0);
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
	attributeAffects(aimVec, twist);
	attributeAffects(upVec, twist);
	attributeAffects(fwdVec, twist);
	attributeAffects(offset, twist);
	attributeAffects(matrix, twist);

	return status;

}

void* TwistReaderNode::creator()
{

	return new TwistReaderNode();

}
