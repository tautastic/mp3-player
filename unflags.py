Import("env")

unflags = env.ParseFlagsExtended(env.get("BUILD_UNFLAGS", []))["CXXFLAGS"]


def drop_unflags(env, node):
    flags = [flag for flag in env.Flatten(env["CXXFLAGS"]) if flag not in unflags]
    return env.Object(node, CXXFLAGS=flags)


env.AddBuildMiddleware(drop_unflags)
