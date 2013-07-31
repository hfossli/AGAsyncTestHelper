#
# Be sure to run `pod spec lint AGAsyncTestHelper.podspec' to ensure this is a
# valid spec and remove all comments before submitting the spec.
#
# To learn more about the attributes see http://docs.cocoapods.org/specification.html
#
Pod::Spec.new do |s|
  s.name = "AGAsyncTestHelper"
  s.version = "0.2"
  s.summary = "Macro for writing unit tests with asynchronous operations."
  s.homepage = "https://github.com/hfossli/AGAsyncTestHelper"
  s.license = { :type => 'MIT', :file => 'LICENSE' }
  s.author = { "Håvard Fossli" => "hfossli@gmail.com" }
  s.source = {
    :git => "https://github.com/hfossli/AGAsyncTestHelper.git",
    :tag => s.version.to_s
    }
  s.source_files = 'Source/*.{h,m}'
  s.requires_arc = true
end
