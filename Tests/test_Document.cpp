#include <catch2/catch_test_macros.hpp>
#include <Util/Juce_Header.h>
#include "Timeline/Objects/Timeline_Document.h"
#include "Timeline/Objects/Timeline_DocumentController.h"




TEST_CASE("Add controller to document")
{
	auto docController = new Timeline::DocumentController();
	auto document = new Timeline::Document(docController);
	CHECK(docController == document->getDocumentController());
}
