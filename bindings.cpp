#include <iostream>

#include <pybind11/pybind11.h>

#include <arrow/python/api.h>
#include <arrow/python/pyarrow.h>
#include <arrow/table.h>

void testImport() {
  int results = arrow::py::import_pyarrow();
  std::cout << "Import results " << results << std::endl;
}


void testSchema() {
  arrow::py::import_pyarrow();
  std::shared_ptr<arrow::Schema> schema = arrow::schema({arrow::field("foo", arrow::utf8())});
  std::cout << *schema << std::endl;
}


PYBIND11_MODULE(bindings, m) {
m.doc() = "pybind11 with pyarrow";
m.def("test_import", &testImport, "Just a dummy test importing arrow");
m.def("test_schema", &testSchema, "Test creating a schema");
}