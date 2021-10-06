#include <iostream>

#include <pybind11/pybind11.h>

#include <arrow/python/api.h>
#include <arrow/array.h>

#include <arrow/python/pyarrow.h>
#include <arrow/table.h>
#include <arrow/builder.h>

#include <arrow/csv/api.h>
#include <arrow/csv/writer.h>
#include <arrow/io/memory.h>


arrow::Status dumpTable(const std::shared_ptr<arrow::Table>& table) {
  auto outputResult = arrow::io::BufferOutputStream::Create();
  ARROW_RETURN_NOT_OK(outputResult.status());
  std::shared_ptr<arrow::io::BufferOutputStream> output = outputResult.ValueOrDie();
  ARROW_RETURN_NOT_OK(arrow::csv::WriteCSV(*table, arrow::csv::WriteOptions::Defaults(), output.get()));
  auto finishResult = output->Finish();
  ARROW_RETURN_NOT_OK(finishResult.status());
  std::cout << finishResult.ValueOrDie()->ToString();
  return arrow::Status::OK();
}

void testImport() {
  int results = arrow::py::import_pyarrow();
  std::cout << "Import results " << results << std::endl;
}


std::shared_ptr<arrow::Table> createTable() {
  arrow::py::import_pyarrow();
  std::shared_ptr<arrow::Schema> schema = arrow::schema({arrow::field("foo", arrow::utf8())});
  std::cout << *schema << std::endl;

  arrow::StringBuilder builder;
  builder.Append("FOO");

  std::vector<std::shared_ptr<arrow::Array>> arrays = {builder.Finish().ValueOrDie()};

  return arrow::Table::Make(
          schema,
          arrays
          );
}

pybind11::object pyCreateTable() {

  auto table = createTable();
  return pybind11::reinterpret_steal<pybind11::object>(arrow::py::wrap_table(table));

}


PYBIND11_MODULE(bindings, m) {
m.doc() = "pybind11 with pyarrow";
m.def("test_import", &testImport, "Just a dummy test importing arrow");
m.def("create_table", &pyCreateTable, "Test creating a table");
}