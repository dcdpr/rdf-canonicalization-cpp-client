// Example application showing how the rdf-canonicalization-cpp library
// could be used. Not yet meant to be the very best example.

// This application reads a jsonld file and, if possible, outputs
// a normalized RDF dataset in NQuads format. This can then be piped
// to a hashing utility like sha256sum and used to compare with RDF
// generated from other documents.

// Usage: jsonld2canon <filename>

#include <jsonld-cpp/FileLoader.h>
#include <jsonld-cpp/JsonLdOptions.h>
#include <rdf-canonicalization-cpp/CanonicalizationProcessor.h>
#include <iostream>
#include <fstream>

int main (int argc, char *argv[]) {

    std::string inputFilename;

    if(argc == 1) {
        std::cout << "No filename argument found" << std::endl;
        return 1;
    }
    if(argc == 2) {
        inputFilename = argv[argc-1];
    }

    std::ifstream fsIn { inputFilename };

    if(fsIn.fail()) {
        std::cout << inputFilename << " not found." << std::endl;
        return 2;
    }

    std::string inputStr {std::istreambuf_iterator<char>(fsIn), std::istreambuf_iterator<char>() };

    if(inputStr.empty()) {
        std::cout << inputFilename << " is empty." << std::endl;
        return 3;
    }

    std::string fileUri = "file://" + inputFilename;

    std::unique_ptr<FileLoader> loader(new FileLoader);
    JsonLdOptions opts(fileUri);
    opts.setDocumentLoader(std::move(loader));

    std::string nquads = CanonicalizationProcessor::canonicalize(fileUri, opts);

    std::cout << nquads;
    std::flush(std::cout);

    return 0;
}
