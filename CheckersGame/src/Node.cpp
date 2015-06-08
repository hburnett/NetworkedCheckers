#include "Node.h"
#include "SpriteBatch.h"

Node::Node()
{
	m_localTransform.CreateIdentity();
	m_parent = nullptr;	

}

Node::Node( Node *parent )
{
	m_localTransform.CreateIdentity();
	parent = nullptr;	
}

Node::~Node()
{


}

void Node::Update( float dt )
{
	//does nothing
}

void Node::Draw( SpriteBatch *sb )
{
	Mat3 worldTransform = GetWorldTransform();

	//Vec2 pos = worldTransform.GetTranslation();
	//Vec2 scale = worldTransform.GetScale();
	//
	//sb->DrawSprite(0, pos.x, pos.y, 16 * scale.x, 16 * scale.y);

	sb->SetColour(1, 1, 1, 1);
	sb->DrawSprite(0, worldTransform, Vec2( 16, 16 ) );
}


//Returns reference to the local transform matrix
Mat3 &Node::Transform()
{
	return m_localTransform;
}

//Calculates the global transform matrix for this node
Mat3 Node::GetWorldTransform()
{
	if(m_parent == nullptr )
	{
		return m_localTransform;
	}
	
	return m_localTransform * m_parent->GetWorldTransform();
}

void Node::AddChild( Node *child )
{
	child->m_parent = this;
}

void Node::RemoveChild( Node *child )
{
	if(child->m_parent == this )
	{
		child->m_parent = nullptr;
	}

}
