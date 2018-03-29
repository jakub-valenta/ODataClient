#include "File.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/filesystem/path.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace OData {
namespace Test {

TEST(FileTest, GetFileTest) {
  File file("test_file", {1, 2, 3, 4});

  const boost::filesystem::path empty;
  ASSERT_EQ(nullptr, file.getFile(empty.begin(), empty.end()));

  const boost::filesystem::path long_path("test_file/too/long");
  ASSERT_EQ(nullptr, file.getFile(long_path.begin(), long_path.end()));

  const boost::filesystem::path path("test_file");
  ASSERT_EQ(&file, file.getFile(path.begin(), path.end()));
}

TEST(FileTest, SerializeTest) {
  std::stringstream sstream(
      std::ios_base::in | std::ios_base::out | std::ios_base::binary);
  File expected("test_file", {1, 2, 3, 4});
  {
    boost::archive::binary_oarchive out(sstream);
    out& expected;
  }

  File deserialized;
  {
    boost::archive::binary_iarchive in(sstream);
    in& deserialized;
  }

  ASSERT_EQ(expected, deserialized);
}

} // namespace Test
} // namespace OData
