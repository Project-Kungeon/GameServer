pushd %~dp0

protoc -I=./ --cpp_out=./ ./Message.proto
protoc -I=./ --cpp_out=./ ./Enum.proto
protoc -I=./ --cpp_out=./ ./Struct.proto
protoc -I=./ --cpp_out=./ ./Skill.proto 
protoc -I=./ --cpp_out=./ ./MonsterPattern.proto 
protoc -I=./ --cpp_out=./ ./GameRound.proto 
protoc -I=./ --cpp_out=./ ./Item.proto 
protoc -I=./ --cpp_out=./ ./Ping.proto 
protoc -I=./ --cpp_out=./ ./Login.proto 
protoc -I=./ --cpp_out=./ ./CharacterSelect.proto 

IF ERRORLEVEL 1 PAUSE

XCOPY /Y Enum.pb.h "../../../BWServer/build/*"
XCOPY /Y Enum.pb.cc "../../../BWServer/build/*"
XCOPY /Y Struct.pb.h "../../../BWServer/build/*"
XCOPY /Y Struct.pb.cc "../../../BWServer/build/*"
XCOPY /Y Message.pb.h "../../../BWServer/build/*"
XCOPY /Y Message.pb.cc "../../../BWServer/build/*"
XCOPY /Y Skill.pb.h "../../../BWServer/build/*"
XCOPY /Y Skill.pb.cc "../../../BWServer/build/*"
XCOPY /Y MonsterPattern.pb.h "../../../BWServer/build/*"
XCOPY /Y MonsterPattern.pb.cc "../../../BWServer/build/*"
XCOPY /Y GameRound.pb.h "../../../BWServer/build/*"
XCOPY /Y GameRound.pb.cc "../../../BWServer/build/*"
XCOPY /Y Item.pb.h "../../../BWServer/build/*"
XCOPY /Y Item.pb.cc "../../../BWServer/build/*"
XCOPY /Y Ping.pb.h "../../../BWServer/build/*"
XCOPY /Y Ping.pb.cc "../../../BWServer/build/*"
XCOPY /Y Login.pb.h "../../../BWServer/build/*"
XCOPY /Y Login.pb.cc "../../../BWServer/build/*"
XCOPY /Y CharacterSelect.pb.h "../../../BWServer/build/*"
XCOPY /Y CharacterSelect.pb.cc "../../../BWServer/build/*"


XCOPY /Y Enum.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Enum.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Struct.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Struct.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Message.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Message.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Skill.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Skill.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y MonsterPattern.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y MonsterPattern.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y GameRound.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y GameRound.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Item.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Item.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Ping.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Ping.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Login.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y Login.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y CharacterSelect.pb.h "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"
XCOPY /Y CharacterSelect.pb.cc "C:/Users/Kang/Desktop/workspace/JK1/Source/JK1/Network/*"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h