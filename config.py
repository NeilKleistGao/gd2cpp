supported_platforms = ["linuxbsd"] # TODO: Add other platforms

def can_build(env, platform):
  env.module_add_dependencies("gd2cpp", ["gdscript"], True)
  return True


def configure(env):
  pass


def get_doc_classes():
  return [
    "GD2CPP",
  ]


def get_doc_path():
  return "doc_classes"
