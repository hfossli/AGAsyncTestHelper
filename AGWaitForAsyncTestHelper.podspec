#
# Be sure to run `pod spec lint AGWaitForAsyncTestHelper.podspec' to ensure this is a
# valid spec and remove all comments before submitting the spec.
#
# To learn more about the attributes see http://docs.cocoapods.org/specification.html
#
Pod::Spec.new do |s|
  s.name = "AGWaitForAsyncTestHelper"
  s.version = "0.1.1"
  s.summary = "The better alternative to NSAssert"
  s.homepage = "https://github.com/hfossli/AGWaitForAsyncTestHelper"
  s.license = { :type => 'MIT', :file => 'LICENSE' }
  s.author = { "Haåvard Fossli" => "hfossli@gmail.com" }
  s.source = {
    :git => "https://github.com/hfossli/AGWaitForAsyncTestHelper.git",
    :tag => s.version.to_s
    }
  s.source_files = 'Source/*.{h,m}'
  s.exclude_files = 'Source/*Test.{h,m}'
  s.requires_arc = true
end
