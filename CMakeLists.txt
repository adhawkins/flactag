cmake_minimum_required(VERSION 3.18.0)
project(flactag VERSION 3.0.0)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

configure_file(config.h.in config.h)
configure_file(ripflac.in ripflac)

find_package(PkgConfig REQUIRED)

pkg_search_module(LIBJPEG REQUIRED libjpeg)
pkg_search_module(SLANG REQUIRED slang)
pkg_search_module(LIBMUSICBRAINZ5CC REQUIRED libmusicbrainz5cc)
pkg_search_module(FLACPP REQUIRED flac++)
pkg_search_module(LIBDISCID REQUIRED libdiscid)
pkg_search_module(UNAC REQUIRED unac)
pkg_search_module(LIBCOVERARTCC REQUIRED libcoverartcc)

add_executable(flactag
	Album.cc
	AlbumWindow.cc
	base64.cc
	CommandLine.cc
	ConfigFile.cc
	CoverArt.cc
	CoverArtFetch.cc
	Cuesheet.cc
	CuesheetTrack.cc
	DiscIDWrapper.cc
	ErrorLog.cc
	FileNameBuilder.cc
	FlacInfo.cc
	flactag.cc
	MusicBrainzInfo.cc
	ScrollableWindow.cc
	TagName.cc
	TagsWindow.cc
	Track.cc
	TrackWindow.cc
	UTF8Tag.cc
	WriteInfo.cc
)

target_link_libraries(flactag
	${LIBJPEG_LIBRARIES}
	${SLANG_LIBRARIES}
	${LIBMUSICBRAINZ5CC_LIBRARIES}
	${FLACPP_LIBRARIES}
	${LIBDISCID_LIBRARIES}
	${UNAC_LIBRARIES}
	${LIBCOVERARTCC_LIBRARIES}
)

add_executable(discid-bin
	discid.cc
	Cuesheet.cc
	CuesheetTrack.cc
	DiscIDWrapper.cc
)

target_link_libraries(discid-bin
	${LIBDISCID_LIBRARIES}
)

set_target_properties(discid-bin PROPERTIES OUTPUT_NAME discid)

find_package(Threads)

add_executable(progressbars
	progressbars.cc
	AlbumRequest.cc
	ProgressBar.cc
	ThreadBase.cc
)

target_link_libraries(progressbars
	${SLANG_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)

find_program(A2X_EXE NAMES a2x REQUIRED)

add_custom_target(manpage ALL DEPENDS flactag.1)
add_custom_command(OUTPUT flactag.1
	MAIN_DEPENDENCY flactag.1.txt
	COMMAND ${A2X_EXE} -f manpage -D ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/flactag.1.txt
)

find_program(ASCIIDOC_EXE NAMES asciidoc REQUIRED)

add_custom_target(webpage ALL DEPENDS flactag.html)
add_custom_command(OUTPUT flactag.html
	MAIN_DEPENDENCY flactag.txt
	COMMAND ${ASCIIDOC_EXE} -a numbered -o ${CMAKE_CURRENT_BINARY_DIR}/flactag.html ${CMAKE_CURRENT_SOURCE_DIR}/flactag.txt
)

install(TARGETS flactag discid-bin)
install(PROGRAMS checkflac ${CMAKE_CURRENT_BINARY_DIR}/ripflac ripdataflac DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES tocfix.sed DESTINATION ${CMAKE_INSTALL_DATADIR}/flactag)
install(FILES flactag.html DESTINATION ${CMAKE_INSTALL_DOCDIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/flactag.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

function(install_manpage_symlink SOURCE TARGET MANDIR)
	set(LINK_COMMAND "\"${CMAKE_COMMAND}\" \"-E\" \"create_symlink\" \"${SOURCE}\" \"${TARGET}\"")

	install(CODE
		"message(STATUS \"Symlinking: \$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/${MANDIR}/${SOURCE} to ${TARGET}\")
		execute_process(
			COMMAND \"${CMAKE_COMMAND}\" \"-E\" \"remove\" \"${TARGET}\"
			WORKING_DIRECTORY \$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/${MANDIR}
		)
		execute_process(
			COMMAND ${LINK_COMMAND}
			WORKING_DIRECTORY \$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/${MANDIR}
			RESULT_VARIABLE EXIT_STATUS
		)
		if(NOT EXIT_STATUS EQUAL 0)
			message(FATAL_ERROR \"Could not create symbolic link from ${CMAKE_INSTALL_PREFIX}/${MANDIR}/${SOURCE} to ${TARGET}\")
		endif()
		set(CMAKE_INSTALL_MANIFEST_FILES \${CMAKE_INSTALL_MANIFEST_FILES} ${CMAKE_INSTALL_PREFIX}/${MANDIR}/${TARGET})"
	)
endfunction(install_manpage_symlink)

install_manpage_symlink(flactag.1 ripflac.1 ${CMAKE_INSTALL_MANDIR}/man1)
install_manpage_symlink(flactag.1 ripdataflac.1 ${CMAKE_INSTALL_MANDIR}/man1)
install_manpage_symlink(flactag.1 checkflac.1 ${CMAKE_INSTALL_MANDIR}/man1)
install_manpage_symlink(flactag.1 discid.1 ${CMAKE_INSTALL_MANDIR}/man1)
