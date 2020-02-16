// RenderNodeManager.h //

#ifndef RENDERNODEMANAGER_H_INCLUDED
#define RENDERNODEMANAGER_H_INCLUDED

class RenderNode;
class RenderSystem;

class RenderNodeManager {
public:
	RenderNodeManager(RenderSystem *p_pxRenderSystem);
	~RenderNodeManager();
	RenderNode *Load(const char *meshName,const char *textureName);
	void Delete(RenderNode* node);

private:
	std::vector<RenderNode*> m_apxRenderNode;
	RenderSystem *m_pxRenderSystem;
};


#endif
