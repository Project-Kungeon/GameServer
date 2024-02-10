pushd %~dp0

protoc -I=./ --cpp_out=./ ./Message.proto
protoc -I=./ --cpp_out=./ ./Enum.proto
protoc -I=./ --cpp_out=./ ./Struct.proto

# 위 작업들이 끝날 때까지 대기
IF ERRORLEVEL 1 PAUSE

# 빌드된 파일들 서버프로젝트에 복사
XCOPY /Y Enum.pb.h "../../../BWServer"
XCOPY /Y Enum.pb.cc "../../../BWServer"
XCOPY /Y Struct.pb.h "../../../BWServer"
XCOPY /Y Struct.pb.cc "../../../BWServer"
XCOPY /Y Message.pb.h "../../../BWServer"
XCOPY /Y Message.pb.cc "../../../BWServer"

# 빌드된 파일들 클라이언트 프로젝트에 복사

# 생성된 파일들 삭제
DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h