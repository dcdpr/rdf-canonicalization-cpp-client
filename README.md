# rdf-canonicalization-cpp-client

This is a simple client application for testing the [rdf-canonicalization-cpp library](https://github.com/dcdpr/rdf-canonicalization-cpp)

## Building rdf-canonicalization-cpp-client

To build rdf-canonicalization-cpp-client, you will need:

* cmake
* g++, clang or Visual Studio (community edition)
* [jsonld-cpp](https://github.com/dcdpr/jsonld-cpp) installed locally
* [rdf-canonicalization-cpp](https://github.com/dcdpr/rdf-canonicalization-cpp) installed locally

rdf-canonicalization-cpp-client uses a pretty standard cmake build system:

```
mkdir build
cd build
cmake ..
make
```

If `jsonld-cpp` and `rdf-canonicalization-cpp` are not installed to a standard location, you will need to provide `cmake` with a prefix path:

```
cmake -DCMAKE_PREFIX_PATH=/tmp/jsonld-install ..
```

### Installing prerequisites

If the above build instruction don't work, you probably need to install some
prerequisites. For example, on a fresh Debian Bullseye system:

```
$ sudo apt install make cmake gcc g++
```

After that, make sure you can build and install `jsonld-cpp` and `rdf-canonicalization-cpp`. See their documention: [jsonld-cpp](https://github.com/dcdpr/jsonld-cpp) and [rdf-canonicalization-cpp](https://github.com/dcdpr/rdf-canonicalization-cpp) for more details.

## Samples

There is a command line application included in rdf-canonicalization-cpp-client and a couple of sample JSON-LD files to use.

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

### jsonld2canon

`jsonld2canon` can convert a JSON-LD document into canonicalized RDF data in NQuads format. This program first runs the ['expansion'](https://www.w3.org/TR/json-ld-api/#expansion) algorithm, then converts the JSON-LD to RDF using ['RDF serialization](https://www.w3.org/TR/json-ld-api/#rdf-serialization-deserialization), and will finally ['canonicalize'](https://json-ld.github.io/rdf-dataset-canonicalization/spec/index.html#canonicalization) (or 'normalize') the result. The canonicalized RDF data will be output to the terminal.

```shell
> ./jsonld2canon ../samples/ex01a.jsonld
```
```
<http://example.com/people/dave> <http://xmlns.com/foaf/0.1/knows> <http://example.com/people/markus> .
<http://example.com/people/dave> <http://xmlns.com/foaf/0.1/name> "Dave Longley" .
<http://example.com/people/gregg> <http://xmlns.com/foaf/0.1/knows> <http://example.com/people/markus> .
<http://example.com/people/gregg> <http://xmlns.com/foaf/0.1/name> "Gregg Kellogg" .
<http://example.com/people/markus> <http://xmlns.com/foaf/0.1/name> "Markus Lanthaler" .
```


One could use `jsonld2canon` with the two sample files included to show how the canonicalized RDF data can be hashed to prove that the two documents are equivalent:

```shell
> ./jsonld2rdf ../samples/ex01a.jsonld | shasum -a 256
cb92d57d8b7abf09e4642338049bd9ee91a0ee0fe327e0a6061a8bbc2f4314bf  -
> ./jsonld2rdf ../samples/ex01b.jsonld | shasum -a 256
cb92d57d8b7abf09e4642338049bd9ee91a0ee0fe327e0a6061a8bbc2f4314bf  -
```


