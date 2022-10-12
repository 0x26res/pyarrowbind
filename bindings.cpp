#include <iostream>

#include <pybind11/pybind11.h>

#include <google/protobuf/descriptor.pb.h>



class MyErrorCollector
        : public google::protobuf::DescriptorPool::ErrorCollector {
public:
    std::string error;
    void AddError(const std::string &, const std::string &,
                  const google::protobuf::Message *, ErrorLocation,
                  const std::string &message) override {
        error.append(message);
        error.append("\n");
    }
};

void doSomeProtoStuff() {
    MyErrorCollector error{};
    std::shared_ptr<google::protobuf::DescriptorPool> pool(
            std::make_shared<google::protobuf::DescriptorPool>());
    std::cout << pool << std::endl;
}

PYBIND11_MODULE(_protobind, m) {
m.doc() = "pybind11 with protobuf";
m.def("do_some_proto_stuff", &doSomeProtoStuff);
}