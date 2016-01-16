##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=WebServer
ConfigurationName      :=Debug
WorkspacePath          := "/home/minya/Developing/Web/WS/WS"
ProjectPath            := "/media/DATA_1/_/Data/Core/Developing/WebServer"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Minya
Date                   :=16/01/16
CodeLitePath           :="/home/minya/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/../bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="WebServer.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            := -Wl,-rpath,/usr/local/lib `pkg-config --libs gupnp-1.0 gssdp-1.0 libxml-2.0 libsoup-2.4` 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./src $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)PocoUtil $(LibrarySwitch)PocoJSON $(LibrarySwitch)PocoNet $(LibrarySwitch)PocoNetSSL $(LibrarySwitch)PocoCrypto $(LibrarySwitch)PocoXML $(LibrarySwitch)PocoFoundation $(LibrarySwitch)PocoData $(LibrarySwitch)PocoDataSQLite $(LibrarySwitch)PocoDataMySQL 
ArLibs                 :=  "PocoUtil" "PocoJSON" "PocoNet" "PocoNetSSL" "PocoCrypto" "PocoXML" "PocoFoundation" "PocoData" "PocoDataSQLite" "PocoDataMySQL" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0    -std=c++11 `pkg-config --cflags gupnp-1.0` $(Preprocessors)
CFLAGS   :=  -g -O0 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
Objects0=$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/view_Index.cpp$(ObjectSuffix) $(IntermediateDirectory)/view_Login.cpp$(ObjectSuffix) $(IntermediateDirectory)/view_Registration.cpp$(ObjectSuffix) $(IntermediateDirectory)/view_User.cpp$(ObjectSuffix) $(IntermediateDirectory)/view_Blog.cpp$(ObjectSuffix) $(IntermediateDirectory)/model_User.cpp$(ObjectSuffix) $(IntermediateDirectory)/model_Service.cpp$(ObjectSuffix) $(IntermediateDirectory)/model_Blog.cpp$(ObjectSuffix) $(IntermediateDirectory)/model_Post.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/model_Rating.cpp$(ObjectSuffix) $(IntermediateDirectory)/model_Category.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_Page.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_Server.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_Util.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_Session.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_UPnP.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_Facet.cpp$(ObjectSuffix) $(IntermediateDirectory)/ctrl_Controller.cpp$(ObjectSuffix) $(IntermediateDirectory)/db_Sql.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/form_Registration.cpp$(ObjectSuffix) $(IntermediateDirectory)/form_User.cpp$(ObjectSuffix) $(IntermediateDirectory)/form_Blog.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:
	@echo Executing Pre Build commands ...
	cpspc ./src/view/Blog.c
	cpspc ./src/view/Index.c
	cpspc ./src/view/Login.c
	cpspc ./src/view/Registration.c
	cpspc ./src/view/User.c
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM "src/main.cpp"

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): src/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) "src/main.cpp"

$(IntermediateDirectory)/view_Index.cpp$(ObjectSuffix): src/view/Index.cpp $(IntermediateDirectory)/view_Index.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/Index.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_Index.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_Index.cpp$(DependSuffix): src/view/Index.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_Index.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/view_Index.cpp$(DependSuffix) -MM "src/view/Index.cpp"

$(IntermediateDirectory)/view_Index.cpp$(PreprocessSuffix): src/view/Index.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_Index.cpp$(PreprocessSuffix) "src/view/Index.cpp"

$(IntermediateDirectory)/view_Login.cpp$(ObjectSuffix): src/view/Login.cpp $(IntermediateDirectory)/view_Login.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/Login.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_Login.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_Login.cpp$(DependSuffix): src/view/Login.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_Login.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/view_Login.cpp$(DependSuffix) -MM "src/view/Login.cpp"

$(IntermediateDirectory)/view_Login.cpp$(PreprocessSuffix): src/view/Login.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_Login.cpp$(PreprocessSuffix) "src/view/Login.cpp"

$(IntermediateDirectory)/view_Registration.cpp$(ObjectSuffix): src/view/Registration.cpp $(IntermediateDirectory)/view_Registration.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/Registration.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_Registration.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_Registration.cpp$(DependSuffix): src/view/Registration.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_Registration.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/view_Registration.cpp$(DependSuffix) -MM "src/view/Registration.cpp"

$(IntermediateDirectory)/view_Registration.cpp$(PreprocessSuffix): src/view/Registration.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_Registration.cpp$(PreprocessSuffix) "src/view/Registration.cpp"

$(IntermediateDirectory)/view_User.cpp$(ObjectSuffix): src/view/User.cpp $(IntermediateDirectory)/view_User.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/User.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_User.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_User.cpp$(DependSuffix): src/view/User.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_User.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/view_User.cpp$(DependSuffix) -MM "src/view/User.cpp"

$(IntermediateDirectory)/view_User.cpp$(PreprocessSuffix): src/view/User.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_User.cpp$(PreprocessSuffix) "src/view/User.cpp"

$(IntermediateDirectory)/view_Blog.cpp$(ObjectSuffix): src/view/Blog.cpp $(IntermediateDirectory)/view_Blog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/view/Blog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/view_Blog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/view_Blog.cpp$(DependSuffix): src/view/Blog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/view_Blog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/view_Blog.cpp$(DependSuffix) -MM "src/view/Blog.cpp"

$(IntermediateDirectory)/view_Blog.cpp$(PreprocessSuffix): src/view/Blog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/view_Blog.cpp$(PreprocessSuffix) "src/view/Blog.cpp"

$(IntermediateDirectory)/model_User.cpp$(ObjectSuffix): src/model/User.cpp $(IntermediateDirectory)/model_User.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/model/User.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/model_User.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/model_User.cpp$(DependSuffix): src/model/User.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/model_User.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/model_User.cpp$(DependSuffix) -MM "src/model/User.cpp"

$(IntermediateDirectory)/model_User.cpp$(PreprocessSuffix): src/model/User.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/model_User.cpp$(PreprocessSuffix) "src/model/User.cpp"

$(IntermediateDirectory)/model_Service.cpp$(ObjectSuffix): src/model/Service.cpp $(IntermediateDirectory)/model_Service.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/model/Service.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/model_Service.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/model_Service.cpp$(DependSuffix): src/model/Service.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/model_Service.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/model_Service.cpp$(DependSuffix) -MM "src/model/Service.cpp"

$(IntermediateDirectory)/model_Service.cpp$(PreprocessSuffix): src/model/Service.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/model_Service.cpp$(PreprocessSuffix) "src/model/Service.cpp"

$(IntermediateDirectory)/model_Blog.cpp$(ObjectSuffix): src/model/Blog.cpp $(IntermediateDirectory)/model_Blog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/model/Blog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/model_Blog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/model_Blog.cpp$(DependSuffix): src/model/Blog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/model_Blog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/model_Blog.cpp$(DependSuffix) -MM "src/model/Blog.cpp"

$(IntermediateDirectory)/model_Blog.cpp$(PreprocessSuffix): src/model/Blog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/model_Blog.cpp$(PreprocessSuffix) "src/model/Blog.cpp"

$(IntermediateDirectory)/model_Post.cpp$(ObjectSuffix): src/model/Post.cpp $(IntermediateDirectory)/model_Post.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/model/Post.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/model_Post.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/model_Post.cpp$(DependSuffix): src/model/Post.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/model_Post.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/model_Post.cpp$(DependSuffix) -MM "src/model/Post.cpp"

$(IntermediateDirectory)/model_Post.cpp$(PreprocessSuffix): src/model/Post.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/model_Post.cpp$(PreprocessSuffix) "src/model/Post.cpp"

$(IntermediateDirectory)/model_Rating.cpp$(ObjectSuffix): src/model/Rating.cpp $(IntermediateDirectory)/model_Rating.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/model/Rating.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/model_Rating.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/model_Rating.cpp$(DependSuffix): src/model/Rating.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/model_Rating.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/model_Rating.cpp$(DependSuffix) -MM "src/model/Rating.cpp"

$(IntermediateDirectory)/model_Rating.cpp$(PreprocessSuffix): src/model/Rating.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/model_Rating.cpp$(PreprocessSuffix) "src/model/Rating.cpp"

$(IntermediateDirectory)/model_Category.cpp$(ObjectSuffix): src/model/Category.cpp $(IntermediateDirectory)/model_Category.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/model/Category.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/model_Category.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/model_Category.cpp$(DependSuffix): src/model/Category.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/model_Category.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/model_Category.cpp$(DependSuffix) -MM "src/model/Category.cpp"

$(IntermediateDirectory)/model_Category.cpp$(PreprocessSuffix): src/model/Category.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/model_Category.cpp$(PreprocessSuffix) "src/model/Category.cpp"

$(IntermediateDirectory)/core_Page.cpp$(ObjectSuffix): src/core/Page.cpp $(IntermediateDirectory)/core_Page.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/core/Page.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_Page.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_Page.cpp$(DependSuffix): src/core/Page.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_Page.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_Page.cpp$(DependSuffix) -MM "src/core/Page.cpp"

$(IntermediateDirectory)/core_Page.cpp$(PreprocessSuffix): src/core/Page.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_Page.cpp$(PreprocessSuffix) "src/core/Page.cpp"

$(IntermediateDirectory)/core_Server.cpp$(ObjectSuffix): src/core/Server.cpp $(IntermediateDirectory)/core_Server.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/core/Server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_Server.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_Server.cpp$(DependSuffix): src/core/Server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_Server.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_Server.cpp$(DependSuffix) -MM "src/core/Server.cpp"

$(IntermediateDirectory)/core_Server.cpp$(PreprocessSuffix): src/core/Server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_Server.cpp$(PreprocessSuffix) "src/core/Server.cpp"

$(IntermediateDirectory)/core_Util.cpp$(ObjectSuffix): src/core/Util.cpp $(IntermediateDirectory)/core_Util.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/core/Util.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_Util.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_Util.cpp$(DependSuffix): src/core/Util.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_Util.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_Util.cpp$(DependSuffix) -MM "src/core/Util.cpp"

$(IntermediateDirectory)/core_Util.cpp$(PreprocessSuffix): src/core/Util.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_Util.cpp$(PreprocessSuffix) "src/core/Util.cpp"

$(IntermediateDirectory)/core_Session.cpp$(ObjectSuffix): src/core/Session.cpp $(IntermediateDirectory)/core_Session.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/core/Session.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_Session.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_Session.cpp$(DependSuffix): src/core/Session.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_Session.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_Session.cpp$(DependSuffix) -MM "src/core/Session.cpp"

$(IntermediateDirectory)/core_Session.cpp$(PreprocessSuffix): src/core/Session.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_Session.cpp$(PreprocessSuffix) "src/core/Session.cpp"

$(IntermediateDirectory)/core_UPnP.cpp$(ObjectSuffix): src/core/UPnP.cpp $(IntermediateDirectory)/core_UPnP.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/core/UPnP.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_UPnP.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_UPnP.cpp$(DependSuffix): src/core/UPnP.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_UPnP.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_UPnP.cpp$(DependSuffix) -MM "src/core/UPnP.cpp"

$(IntermediateDirectory)/core_UPnP.cpp$(PreprocessSuffix): src/core/UPnP.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_UPnP.cpp$(PreprocessSuffix) "src/core/UPnP.cpp"

$(IntermediateDirectory)/core_Facet.cpp$(ObjectSuffix): src/core/Facet.cpp $(IntermediateDirectory)/core_Facet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/core/Facet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_Facet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_Facet.cpp$(DependSuffix): src/core/Facet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_Facet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_Facet.cpp$(DependSuffix) -MM "src/core/Facet.cpp"

$(IntermediateDirectory)/core_Facet.cpp$(PreprocessSuffix): src/core/Facet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_Facet.cpp$(PreprocessSuffix) "src/core/Facet.cpp"

$(IntermediateDirectory)/ctrl_Controller.cpp$(ObjectSuffix): src/ctrl/Controller.cpp $(IntermediateDirectory)/ctrl_Controller.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/ctrl/Controller.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ctrl_Controller.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ctrl_Controller.cpp$(DependSuffix): src/ctrl/Controller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ctrl_Controller.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ctrl_Controller.cpp$(DependSuffix) -MM "src/ctrl/Controller.cpp"

$(IntermediateDirectory)/ctrl_Controller.cpp$(PreprocessSuffix): src/ctrl/Controller.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ctrl_Controller.cpp$(PreprocessSuffix) "src/ctrl/Controller.cpp"

$(IntermediateDirectory)/db_Sql.cpp$(ObjectSuffix): src/core/db/Sql.cpp $(IntermediateDirectory)/db_Sql.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/core/db/Sql.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/db_Sql.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/db_Sql.cpp$(DependSuffix): src/core/db/Sql.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/db_Sql.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/db_Sql.cpp$(DependSuffix) -MM "src/core/db/Sql.cpp"

$(IntermediateDirectory)/db_Sql.cpp$(PreprocessSuffix): src/core/db/Sql.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/db_Sql.cpp$(PreprocessSuffix) "src/core/db/Sql.cpp"

$(IntermediateDirectory)/form_Registration.cpp$(ObjectSuffix): src/ctrl/form/Registration.cpp $(IntermediateDirectory)/form_Registration.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/ctrl/form/Registration.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/form_Registration.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/form_Registration.cpp$(DependSuffix): src/ctrl/form/Registration.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/form_Registration.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/form_Registration.cpp$(DependSuffix) -MM "src/ctrl/form/Registration.cpp"

$(IntermediateDirectory)/form_Registration.cpp$(PreprocessSuffix): src/ctrl/form/Registration.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/form_Registration.cpp$(PreprocessSuffix) "src/ctrl/form/Registration.cpp"

$(IntermediateDirectory)/form_User.cpp$(ObjectSuffix): src/ctrl/form/User.cpp $(IntermediateDirectory)/form_User.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/ctrl/form/User.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/form_User.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/form_User.cpp$(DependSuffix): src/ctrl/form/User.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/form_User.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/form_User.cpp$(DependSuffix) -MM "src/ctrl/form/User.cpp"

$(IntermediateDirectory)/form_User.cpp$(PreprocessSuffix): src/ctrl/form/User.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/form_User.cpp$(PreprocessSuffix) "src/ctrl/form/User.cpp"

$(IntermediateDirectory)/form_Blog.cpp$(ObjectSuffix): src/ctrl/form/Blog.cpp $(IntermediateDirectory)/form_Blog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/DATA_1/_/Data/Core/Developing/WebServer/src/ctrl/form/Blog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/form_Blog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/form_Blog.cpp$(DependSuffix): src/ctrl/form/Blog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/form_Blog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/form_Blog.cpp$(DependSuffix) -MM "src/ctrl/form/Blog.cpp"

$(IntermediateDirectory)/form_Blog.cpp$(PreprocessSuffix): src/ctrl/form/Blog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/form_Blog.cpp$(PreprocessSuffix) "src/ctrl/form/Blog.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


