pushd %~dp0

protoc -I=./ --cpp_out=./ ./Message.proto
protoc -I=./ --cpp_out=./ ./Enum.proto
protoc -I=./ --cpp_out=./ ./Struct.proto


IF ERRORLEVEL 1 PAUSE

XCOPY /Y Enum.pb.h "../../../BWServer"
XCOPY /Y Enum.pb.cc "../../../BWServer"
XCOPY /Y Struct.pb.h "../../../BWServer"
XCOPY /Y Struct.pb.cc "../../../BWServer"
XCOPY /Y Message.pb.h "../../../BWServer"
XCOPY /Y Message.pb.cc "../../../BWServer"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h