class StringVariables:
    def __init__(self, build_dir, proj_name):
        self.build_dir = build_dir
        self.proj_name = proj_name

    def parse(self, text: str):
        return (text
                .replace("{out}", self.build_dir))