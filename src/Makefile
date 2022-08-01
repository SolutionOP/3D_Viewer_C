CC = gcc
GCOV = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
QMAKE = qmake
INSTALL_DIR = 3DViewer
ifeq ($(OS), Linux)
  BUILD_DIR = build-3D_Viewer_v1-Desktop_x86_darwin_generic_mach_o_64bit-Debug
  APP_DIR=
  LIBS = -lcheck -lm -lpthread -lsubunit -lrt
  OPEN = xdg-open
else
  BUILD_DIR = build-3D_Viewer_v1-Desktop_x86_darwin_generic_mach_o_64bit-Debug/
  APP_DIR=3D_Viewer_v1.app/Contents/MacOS
  LIBS = -lcheck
  OPEN = open
endif

all: build

build:
	$(QMAKE) -o $(BUILD_DIR)/Makefile ./3DViewer_v1.0_SourceCode/3D_Viewer_v1.pro
	make -C $(BUILD_DIR)/

rebuild: clean all

install:
	mkdir $(INSTALL_DIR)
	install $(BUILD_DIR)$(APP_DIR)/3D_Viewer_v1 $(INSTALL_DIR)/3D_Viewer_v1

uninstall:
	rm -rf $(INSTALL_DIR)

dvi:
	# mkdir $(INSTALL_DIR)/readme
	cp -rf readme $(INSTALL_DIR)
	open $(INSTALL_DIR)/readme/man.md

dist:
	tar -cf 3D_Viewer_v1.tar readme 3DViewer_v1.0_SourceCode models Makefile 

tests: 3d_viewer.a
	cd 3DViewer_v1.0_SourceCode && $(CC) $(GCOV) tests.c 3d_viewer.a $(LIBS) -o gcov_report && ./gcov_report

3d_viewer.a: 
	cd 3DViewer_v1.0_SourceCode && $(CC) $(GCOV) -c parser.c affine_transformations.c && \
	ar rcs 3d_viewer.a affine_transformations.o parser.o && rm *.o

gcov_report: tests
	cd 3DViewer_v1.0_SourceCode && lcov -t "gcov_report" -o ../gcov_report.info -c -d . && \
	genhtml -o ../report ../gcov_report.info && $(OPEN) ../report/index.html

check:
	python3 ../materials/linters/cpplint.py --extensions=c 3DViewer_v1.0_SourceCode/*.c

clean:
	rm -rf ./report build* $(INSTALL_DIR)
	rm -f *.info  *.tar
	cd 3DViewer_v1.0_SourceCode && rm -f *.gcno *.gcda gcov_report *.o *.a
	cd ..
