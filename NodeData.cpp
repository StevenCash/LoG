#include "NodeData.h"
#include "tinyxml2.h"

#include <iostream>


NodeData::NodeData()
{
  //Example code for loading a dummy xml file
  tinyxml2::XMLDocument doc;
  tinyxml2::XMLError errorCode = doc.LoadFile("dummy.xml");
  if (errorCode != tinyxml2::XML_SUCCESS)
    {
      std::cerr << "Error loading XML file" << std::endl;
    }
  else
    {
      //Note that the root element may not actually have any value of its own
      //it could just be the root of the document
      //use named children to get specific elements
      tinyxml2::XMLNode *pRoot = doc.RootElement();
      if(!pRoot)
	{
	  std::cerr << "Error getting root element" << std::endl;
	}
      else
	{
	  //Using a named child to get an element
	  tinyxml2::XMLElement *pElement = pRoot->FirstChildElement("roomId");
	  if(!pElement)
	    {
	      std::cerr << "Error getting roomId" << std::endl;
	    }
	  else
	    {
	      //Translating the data from a named element into an integer
	      int roomId = 0;
	      pElement->QueryIntText(&roomId);
	      std::cerr << "Found roomId: " << roomId << std::endl;
	    }

	  pElement = pRoot->FirstChildElement("someFloat");
	  if(!pElement)
	    {
	      std::cerr << "Error getting someFloat" << std::endl;
	    }
	  else
	    {
	      //Translating the data from a named element into an float
	      float someFloat = 0;
	      pElement->QueryFloatText(&someFloat);
	      std::cerr << "Found someFloat: " << someFloat << std::endl;

	      //Or just getting the value as text.  Note that this must be a const char*
	      const char *pChar = pElement->GetText();
	      std::cout << "Text string of someFloat: " << pChar << std::endl;

	      //Loop through the all the element (note unnamed child)
	      pElement = pRoot->FirstChildElement();
	      while(pElement != 0 )
		{
		  const char *pChar = pElement->GetText();
		  std::cout << "Text string: " << pChar << std::endl;
		  pElement = pElement->NextSiblingElement();
		}

	      //iterate through named elements
	      pElement = pRoot->FirstChildElement("roomId");
	      while(pElement != 0 )
		{
		  const char *pChar = pElement->GetText();
		  std::cout << "RoomId string: " << pChar << std::endl;
		  //and get the next named sibling
		  pElement = pElement->NextSiblingElement("roomId");
		}
	      

	    }

	  
	}
    }
}

NodeData::~NodeData()
{
}
