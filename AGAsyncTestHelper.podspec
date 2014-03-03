Pod::Spec.new do |s|
  s.name = "AGAsyncTestHelper"
  s.version = "1.0"
  s.summary = "Macro for writing unit tests with asynchronous operations."
  s.homepage = "https://github.com/hfossli/AGAsyncTestHelper"
  s.license = { :type => 'MIT', :file => 'LICENSE' }
  s.author = { "Håvard Fossli" => "hfossli@gmail.com" }
  s.source = {
    :git => "https://github.com/hfossli/AGAsyncTestHelper.git",
    :branch => "develop"
    }
  s.source_files = 'Source/*.{h,m}'
  s.requires_arc = false

  s.subspec 'Shorthand' do |ss|
    ss.prefix_header_contents = '#define AGWW_SHORTHAND'
  end

end
