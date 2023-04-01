#include "Timeline_Document.h"
#include "Timeline_DocumentController.h"
#include "Timeline_AudioSource.h"

using namespace Timeline;

Document::Document(Timeline::DocumentController* doc)
: docController(doc)
{
	
}

Document::~Document()
{
	docController = nullptr;
}

Timeline::DocumentController* Document::getDocumentController()
{
	return docController;
}

void Document::addAudioSource(Timeline::AudioSource source)
{
	//audioSources.push_back(source);
}
