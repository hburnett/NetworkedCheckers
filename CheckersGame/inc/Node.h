//Author: Heath Burnett
//Credit to Aaron Cox
//
//Description: Node class, allows for parents of objects
//Classes that inherit from Node will be "parentable"

#ifndef	NODE_H
#define	NODE_H

#include "Mat3.h"

class SpriteBatch;

class Node
{
public:

	Node();
	Node( Node *parent );

	virtual ~Node();

	virtual void Update( float dt );
	virtual void Draw( SpriteBatch *sb );

	//Returns reference to the local transform matrix
	Mat3 &Transform();

	//Calculates the global transform matrix for this node
	Mat3 GetWorldTransform();

	void AddChild( Node *child );
	void RemoveChild( Node *child );

protected:

	Mat3 m_localTransform;

	Node *m_parent;


};
#endif