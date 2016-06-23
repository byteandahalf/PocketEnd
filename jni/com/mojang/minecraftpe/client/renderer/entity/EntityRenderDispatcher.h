#pragma once

struct EntityRendererId;
struct EntityRenderer;

struct EntityRenderDispatcher
{
	EntityRenderer* getRenderer(EntityRendererId);

	char filler[12];
	EntityRenderer* renderers[35];
};
