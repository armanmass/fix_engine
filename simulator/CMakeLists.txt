find_package(Python3 COMPONENTS Interpreter REQUIRED)

add_custom_target(
    fix_python_client ALL
    COMMAND ${Python3_EXECUTABLE} -m venv venv || true
    COMMAND venv/bin/pip install -r ${CMAKE_CURRENT_SOURCE_DIR}/requirements.txt
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Installing Python FIX client dependencies in virtual environment."
)