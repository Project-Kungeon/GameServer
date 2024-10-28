pushd %~dp0

protoc -I=./ --cpp_out=./ ./Message.proto
protoc -I=./ --cpp_out=./ ./Enum.proto
protoc -I=./ --cpp_out=./ ./Struct.proto
protoc -I=./ --cpp_out=./ ./Skill.proto 
protoc -I=./ --cpp_out=./ ./MonsterPattern.proto 
protoc -I=./ --cpp_out=./ ./GameRound.proto 
protoc -I=./ --cpp_out=./ ./Item.proto 
protoc -I=./ --cpp_out=./ ./Ping.proto 

IF ERRORLEVEL 1 PAUSE

XCOPY /Y Enum.pb.h "../../../BWServer/*"
XCOPY /Y Enum.pb.cc "../../../BWServer/*"
XCOPY /Y Struct.pb.h "../../../BWServer/*"
XCOPY /Y Struct.pb.cc "../../../BWServer/*"
XCOPY /Y Message.pb.h "../../../BWServer/*"
XCOPY /Y Message.pb.cc "../../../BWServer/*"
XCOPY /Y Skill.pb.h "../../../BWServer/*"
XCOPY /Y Skill.pb.cc "../../../BWServer/*"
XCOPY /Y MonsterPattern.pb.h "../../../BWServer/*"
XCOPY /Y MonsterPattern.pb.cc "../../../BWServer/*"
XCOPY /Y GameRound.pb.h "../../../BWServer/*"
XCOPY /Y GameRound.pb.cc "../../../BWServer/*"
XCOPY /Y Item.pb.h "../../../BWServer/*"
XCOPY /Y Item.pb.cc "../../../BWServer/*"
XCOPY /Y Ping.pb.h "../../../BWServer/*"
XCOPY /Y Ping.pb.cc "../../../BWServer/*"


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

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h