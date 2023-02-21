#include <node.h>

// C:\Users\frank\AppData\Local\node-gyp\Cache\19.6.1\include\node

void Hello(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  if (args.Length() < 1 && !args[0]->IsString())
  {
    isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Requires one parameter that is a string").ToLocalChecked()));
    return;
  }

  auto arg0(*v8::String::Utf8Value(isolate, args[0].As<v8::String>()));
  auto result = v8::String::Concat(isolate,
                                   v8::String::NewFromUtf8(isolate, "Hello, ").ToLocalChecked(),
                                   v8::String::NewFromUtf8(isolate, arg0).ToLocalChecked());

  args.GetReturnValue().Set(result);
}

void Foo(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  // the first arg should be a callback
  if (args.Length() < 1 && !args[0]->IsFunction())
  {
    isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Requires one parameter that is a function").ToLocalChecked()));
    return;
  }

  // get reference to the callback
  auto callback = args[0].As<v8::Function>();

  // call the callback
  const unsigned argc = 1;
  v8::Local<v8::Value> recv = v8::Integer::New(isolate, 0);
  v8::Local<v8::Value> argv[argc] = {v8::String::NewFromUtf8(isolate, "This is so cool!").ToLocalChecked()};
  callback->Call(isolate->GetCurrentContext(), recv, argc, argv);
}

void Bar(const v8::FunctionCallbackInfo<v8::Value> &args)
{
  v8::Isolate *isolate = args.GetIsolate();

  // create a new object
  v8::Local<v8::Object> obj = v8::Object::New(isolate);
  // set a property on the object called hello with a value of "world"
  obj->Set(isolate->GetCurrentContext(),
           v8::String::NewFromUtf8(isolate, "hello").ToLocalChecked(),
           v8::String::NewFromUtf8(isolate, "world").ToLocalChecked());

  args.GetReturnValue().Set(obj);
}

void Initialize(v8::Local<v8::Object> exports)
{
  NODE_SET_METHOD(exports, "hello", Hello);
  NODE_SET_METHOD(exports, "foo", Foo);
  NODE_SET_METHOD(exports, "bar", Bar);
}

NODE_MODULE(module_name, Initialize)