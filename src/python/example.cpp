#include <boost/python.hpp>

#include "python/example_c.h"

using namespace ::boost::python;

BOOST_PYTHON_MODULE(example) {
  def("GetString", GetString);
  def("GetInt", GetInt);

  class_<Example>("Example", init<>())
        .def("GetInt", &Example::GetInt)
        .def("IncInt", &Example::IncInt)
        .def("DecInt", &Example::DecInt);

}

