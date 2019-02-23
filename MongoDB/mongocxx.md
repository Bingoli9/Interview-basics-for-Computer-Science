## mongocxx

### Prerequisites

```C++
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
```

### Make a Connection

```C++
mongocxx::instance instance{}; // This should be done only once.
mongocxx::uri uri("mongodb://localhost:27017");
mongocxx::client client(uri);
```

## Access a Database

```C++
mongocxx::database db = client["mydb"];
```

## Access a Collection

```C++
mongocxx::collection coll = db["test"];
```

## Create a Document

For example, consider the following JSON document:

```C++
{
   "name" : "MongoDB",
   "type" : "database",
   "count" : 1,
   "versions": [ "v3.2", "v3.0", "v2.6" ],
   "info" : {
               "x" : 203,
               "y" : 102
            }
}
```

```C++
auto builder = bsoncxx::builder::stream::document{};
bsoncxx::document::value doc_value = builder
  << "name" << "MongoDB"
  << "type" << "database"
  << "count" << 1
  << "versions" << bsoncxx::builder::stream::open_array
    << "v3.2" << "v3.0" << "v2.6"
  << close_array
  << "info" << bsoncxx::builder::stream::open_document
    << "x" << 203
    << "y" << 102
  << bsoncxx::builder::stream::close_document
  << bsoncxx::builder::stream::finalize;
```

Use `bsoncxx::builder::stream::finalize` to obtain a [`bsoncxx::document::value`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classbsoncxx_1_1document_1_1value.html) instance.

This `bsoncxx::document::value` type is a read-only object owning its own memory. To use it, you must obtain a [`bsoncxx::document::view`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classbsoncxx_1_1document_1_1view.html) using the `view()` method:

```C++
bsoncxx::document::view view = doc_value.view();
```

You can access fields within this document view using `operator[]`, which will return a[`bsoncxx::document::element`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classbsoncxx_1_1document_1_1element.html) instance. For example, the following will extract the `name` field whose value is a string:

```C++
bsoncxx::document::element element = view["name"];
if(element.type() != bsoncxx::type::k_utf8) {
  // Error
}
std::string name = element.get_utf8().value.to_string();
```

If the value in the `name` field is not a string and you do not include a type guard as seen in the preceding example, this code will throw an instance of [`bsoncxx::exception`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classbsoncxx_1_1exception.html).

## Insert Documents

### Insert One Document

To insert a single document into the collection, use a [`mongocxx::collection`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classmongocxx_1_1collection.html) instance’s `insert_one()`method:

```C++
bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
 restaurants.insert_one(doc);
```

If you do not specify a top-level `_id` field in the document, MongoDB automatically adds an `_id` field to the inserted document.

You can obtain this value using the `inserted_id()` method of the returned[`mongocxx::result::insert_one`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classmongocxx_1_1result_1_1insert__one.html) instance.

### Insert Multiple Documents

To insert multiple documents to the collection, use a [`mongocxx::collection`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classmongocxx_1_1collection.html) instance’s `insert_many()`method, which takes a list of documents to insert.

The following example will add multiple documents of the form:

```C++
{ "i" : value }
```

Create the documents in a loop and add to the documents list:

```C++
std::vector<bsoncxx::document::value> documents;
for(int i = 0; i < 100; i++) {
    documents.push_back(
      bsoncxx::builder::stream::document{} << "i" << i << finalize);
}
```

To insert these documents to the collection, pass the list of documents to the `insert_many()` method.

```C++
collection.insert_many(documents);
```

If you do not specify a top-level `_id` field in each document, MongoDB automatically adds a `_id` field to the inserted documents.

You can obtain this value using the `inserted_ids()` method of the returned[`mongocxx::result::insert_many`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classmongocxx_1_1result_1_1insert__many.html) instance.

## Query the Collection

o query the collection, use the collection’s `find()` and `find_one` methods.

find()  will return an instance of mongocxx::cursor, while `find_one()` will return an instance of`std::optional\<bsoncxx::document::value\>

You can call either method with an empty document to query all documents in a collection, or pass a filter to query for documents that match the filter criteria.

### Find a Single Document in a Collection

To return a single document in the collection, use the `find_one()` method without any parameters.

```C++
bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
  collection.find_one({});
if(maybe_result) {
  // Do something with *maybe_result;
}
```

### Find All Documents in a Collection

```C++
mongocxx::cursor cursor = collection.find({});
for(auto doc : cursor) {
  std::cout << bsoncxx::to_json(doc) << "\n";
}
```

### Specify a Query Filter

#### Get A Single Document That Matches a Filter

To find the first document where the field `i` has the value `71`, pass the document `{"i": 71}` to specify the equality condition:

```C++
bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
  collection.find_one(document{} << "i" << 71 << finalize);
if(maybe_result) {
  std::cout << bsoncxx::to_json(*maybe_result) << "\n";
}
```

#### Get All Documents That Match a Filter

The following example returns and prints all documents where `50 < "i" <= 100`:

```C++
mongocxx::cursor cursor = collection.find(
  document{} << "i" << open_document <<
    "$gt" << 50 <<
    "$lte" << 100
  << close_document << finalize);
for(auto doc : cursor) {
  std::cout << bsoncxx::to_json(doc) << "\n";
}
```

## Update Documents

To update documents in a collection, you can use the collection’s `update_one()` and `update_many()`methods.

The update methods return an instance of `std::optional<`[`mongocxx::result::update`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classmongocxx_1_1result_1_1update.html)`>`, which provides information about the operation including the number of documents modified by the update.

### Update a Single Document

To update at most one document, use the `update_one()` method.

The following example updates the first document that matches the filter `{ "i": 10 }` and sets the value of `i` to `110`:

```C++
collection.update_one(document{} << "i" << 10 << finalize,
                      document{} << "$set" << open_document <<
                        "i" << 110 << close_document << finalize);
```

### Update Multiple Documents

To update all documents matching a filter, use the `update_many()` method.

The following example increments the value of `i` by `100` where `i` is less than `100`:

```C++
bsoncxx::stdx::optional<mongocxx::result::update> result =
 collection.update_many(
  document{} << "i" << open_document <<
    "$lt" << 100 << close_document << finalize,
  document{} << "$inc" << open_document <<
    "i" << 100 << close_document << finalize);

if(result) {
  std::cout << result->modified_count() << "\n";
}
```



## Delete Documents

To delete documents from a collection, you can use a collection’s `delete_one()` and `delete_many()`methods.

The delete methods return an instance of `std::optional<`[`mongocxx::result::delete`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classmongocxx_1_1result_1_1delete__result.html)`>`, which contains the number of documents deleted.

### Delete a Single Document

To delete at most a single document that matches a filter, use the `delete_one()` method.

For example, to delete a document that matches the filter `{ "i": 110 }`:

```C++
collection.delete_one(document{} << "i" << 110 << finalize);
```

### Delete All Documents That Match a Filter

To delete all documents matching a filter, use a collection’s `delete_many()` method.

The following example deletes all documents where `i` is greater or equal to `100`:

```C++
bsoncxx::stdx::optional<mongocxx::result::delete_result> result =
 collection.delete_many(
  document{} << "i" << open_document <<
    "$gte" << 100 << close_document << finalize);

if(result) {
  std::cout << result->deleted_count() << "\n";
}
```

## Create Indexes

To create an [index](https://docs.mongodb.com/master/indexes/) on a field or set of fields, pass an index specification document to the`create_index()` method of a [`mongocxx::collection`](https://mongodb.github.io/mongo-cxx-driver/api/mongocxx-v3/classmongocxx_1_1collection.html) instance. An index key specification document contains the fields to index and the index type for each field:

```C++
{ "index1": "<type>", "index2": <type> }
```

- For an ascending index type, specify 1 for `<type>`.
- For a descending index type, specify -1 for `<type>`.

The following example creates an ascending index on the `i` field:

```C++
auto index_specification = document{} << "i" << 1 << finalize;
collection.create_index(std::move(index_specification));
```

