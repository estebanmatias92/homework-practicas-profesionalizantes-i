 /**
* Copyright (c) 2020 ISFT N°151. All rights reserved.
* Released under the MIT license
* https://opensource.org/licenses/MIT
**/

 #include <iostream>
 #include <fstream>

 #include "cgicc/CgiDefs.h"
 #include "cgicc/Cgicc.h"
 #include "cgicc/HTTPHTMLHeader.h"
 #include "cgicc/HTMLClasses.h"

 #include "./include/uuid.hpp"

using namespace cgicc;

int main(int /*argc*/, char ** /*argv*/)
{
    std::cout << "Content-Type:text/plain;charset=utf-8\n\n";

    // Create a new Cgicc object containing all the CGI data
    Cgicc cgi;
    
    // Obtiene el archivo que fue enviado mendiante el formulario.
    const_file_iterator file = cgi.getFile(".pdf");
   
    form_iterator name      = cgi.getElement("name");
    form_iterator author    = cgi.getElement("author");
    form_iterator topic     = cgi.getElement("topic");
    
    if(file->getDataLength() != 0)
    {
        std::string uniqueID = uuid::generate_uuid_v4();

        std::ofstream saveFile("./uploaded_files/" + uniqueID);
        file->writeToStream(saveFile);
        saveFile.close();   
        std::cout << "Upload Success!" << std::endl; 

        std::ofstream saveData("./data.csv", std::ios::app);
        saveData << name->getValue()    << "," 
                 << author->getValue()  << "," 
                 << topic->getValue()   << ","
                 << file->getFilename() << ","
                 << uniqueID            << "\n";
        saveData.close();
    }
    else
    {
        std::cout << "Error uploading file" << std::endl;
    }
     
    return 0;
}
