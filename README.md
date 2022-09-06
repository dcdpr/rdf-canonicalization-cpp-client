# jsonld-cpp-client

This is a simple client application for testing the [jsonld-cpp library](https://github.com/dcdpr/jsonld-cpp)

## Building jsonld-cpp-client

To build jsonld-cpp-client, you will need:

* cmake
* g++, clang or Visual Studio (community edition)
* [jsonld-cpp](https://github.com/dcdpr/jsonld-cpp) installed locally

jsonld-cpp-client uses a pretty standard cmake build system:

```
mkdir build
cd build
cmake ..
make
```

If `jsonld-cpp` is not installed to a standard location, you will need to provide `cmake` with a prefix path:

```
cmake -DCMAKE_PREFIX_PATH=/tmp/jsonld-install ..
```

### Installing prerequisites

If the above build instruction don't work, you probably need to install some
prerequisites. For example, on a fresh Debian Bullseye system:

```
$ sudo apt install make cmake gcc g++
```

After that, make sure you can build and install `jsonld-cpp`. See its [documentation](https://github.com/dcdpr/jsonld-cpp) for more details.

## Samples

There are two command line applications included in jsonld-cpp-client and a couple of sample JSON-LD files to use.

```shell
> cat ../samples/ex01a.jsonld
```
```json
{
  "@context": {
    "name": "http://xmlns.com/foaf/0.1/name",
    "isKnownBy": { "@reverse": "http://xmlns.com/foaf/0.1/knows", "@container": "@index" }
  },
  "@id": "http://example.com/people/markus",
  "name": "Markus Lanthaler",
  "isKnownBy": {
    "Dave": {
      "@id": "http://example.com/people/dave",
      "name": "Dave Longley"
    },
    "Gregg": {
      "@id": "http://example.com/people/gregg",
      "name": "Gregg Kellogg"
    }
  }
}
```
```shell
> cat ../samples/ex01b.jsonld
```
```json
{ "@context": { "name": "http://xmlns.com/foaf/0.1/name", "isKnownBy": { "@reverse": "http://xmlns.com/foaf/0.1/knows", "@container": "@index" } }, "@id": "http://example.com/people/markus", "isKnownBy": { "Dave": { "@id": "http://example.com/people/dave", "name": "Dave Longley" }, "Gregg": { "@id": "http://example.com/people/gregg", "name": "Gregg Kellogg" } }, "name": "Markus Lanthaler" } 
```

### expand-jsonld

`expand-jsonld` will take a JSON-LD file and run the ['expansion'](https://www.w3.org/TR/json-ld-api/#expansion) algorithm. The expanded file will be output to the terminal.

```shell
> ./expand-jsonld ../samples/ex01a.jsonld  | jq
```
```json
[
  {
    "@id": "http://example.com/people/markus",
    "@reverse": {
      "http://xmlns.com/foaf/0.1/knows": [
        {
          "@id": "http://example.com/people/dave",
          "@index": "Dave",
          "http://xmlns.com/foaf/0.1/name": [
            {
              "@value": "Dave Longley"
            }
          ]
        },
        {
          "@id": "http://example.com/people/gregg",
          "@index": "Gregg",
          "http://xmlns.com/foaf/0.1/name": [
            {
              "@value": "Gregg Kellogg"
            }
          ]
        }
      ]
    },
    "http://xmlns.com/foaf/0.1/name": [
      {
        "@value": "Markus Lanthaler"
      }
    ]
  }
]
```


### jsonld2rdf

`jsonld2rdf` can convert a JSON-LD document into normalized RDF data in NQuads format. This program first runs the ['expansion'](https://www.w3.org/TR/json-ld-api/#expansion) algorithm, then converts the JSON-LD to RDF using ['RDF serialization](https://www.w3.org/TR/json-ld-api/#rdf-serialization-deserialization), and will finally ['normalize'](https://json-ld.github.io/rdf-dataset-canonicalization/spec/index.html#canonicalization) (or 'canonicalize') the result. The normalized RDF data will be output to the terminal.

```shell
> ./jsonld2rdf ../samples/ex01a.jsonld
```
```
<http://example.com/people/dave> <http://xmlns.com/foaf/0.1/knows> <http://example.com/people/markus> .
<http://example.com/people/dave> <http://xmlns.com/foaf/0.1/name> "Dave Longley" .
<http://example.com/people/gregg> <http://xmlns.com/foaf/0.1/knows> <http://example.com/people/markus> .
<http://example.com/people/gregg> <http://xmlns.com/foaf/0.1/name> "Gregg Kellogg" .
<http://example.com/people/markus> <http://xmlns.com/foaf/0.1/name> "Markus Lanthaler" .
```


One could use `jsonld2rdf` with the two sample files included to show how the normalized RDF can be hashed to prove that the two documents are equivalent:

```shell
> ./jsonld2rdf ../samples/ex01a.jsonld | shasum -a 256
cb92d57d8b7abf09e4642338049bd9ee91a0ee0fe327e0a6061a8bbc2f4314bf  -
> ./jsonld2rdf ../samples/ex01b.jsonld | shasum -a 256
cb92d57d8b7abf09e4642338049bd9ee91a0ee0fe327e0a6061a8bbc2f4314bf  -
```


