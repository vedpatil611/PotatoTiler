# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  GLFW_config = debug
  GLAD_config = debug
  ImGui_config = debug
  PotatoTiler_config = debug
  SceneTree_config = debug
endif
ifeq ($(config),release)
  GLFW_config = release
  GLAD_config = release
  ImGui_config = release
  PotatoTiler_config = release
  SceneTree_config = release
endif

PROJECTS := GLFW GLAD ImGui PotatoTiler SceneTree

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

GLFW:
ifneq (,$(GLFW_config))
	@echo "==== Building GLFW ($(GLFW_config)) ===="
	@${MAKE} --no-print-directory -C Dependencies/GLFW -f Makefile config=$(GLFW_config)
endif

GLAD:
ifneq (,$(GLAD_config))
	@echo "==== Building GLAD ($(GLAD_config)) ===="
	@${MAKE} --no-print-directory -C Dependencies/GLAD -f Makefile config=$(GLAD_config)
endif

ImGui:
ifneq (,$(ImGui_config))
	@echo "==== Building ImGui ($(ImGui_config)) ===="
	@${MAKE} --no-print-directory -C Dependencies/ImGui -f Makefile config=$(ImGui_config)
endif

PotatoTiler: GLFW GLAD SceneTree ImGui
ifneq (,$(PotatoTiler_config))
	@echo "==== Building PotatoTiler ($(PotatoTiler_config)) ===="
	@${MAKE} --no-print-directory -C PotatoTiler -f Makefile config=$(PotatoTiler_config)
endif

SceneTree:
ifneq (,$(SceneTree_config))
	@echo "==== Building SceneTree ($(SceneTree_config)) ===="
	@${MAKE} --no-print-directory -C SceneTree -f Makefile config=$(SceneTree_config)
endif

clean:
	@${MAKE} --no-print-directory -C Dependencies/GLFW -f Makefile clean
	@${MAKE} --no-print-directory -C Dependencies/GLAD -f Makefile clean
	@${MAKE} --no-print-directory -C Dependencies/ImGui -f Makefile clean
	@${MAKE} --no-print-directory -C PotatoTiler -f Makefile clean
	@${MAKE} --no-print-directory -C SceneTree -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   GLFW"
	@echo "   GLAD"
	@echo "   ImGui"
	@echo "   PotatoTiler"
	@echo "   SceneTree"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"