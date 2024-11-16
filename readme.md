<link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">

# minig
<div align="center">
  <h3>A topsy-turvy OpenGL wrapper. Grown with ❤️. </h3>
  <p>엉망진창 만들어진 OpenGL 래퍼. 사랑과 함께.</p>
</div>

## To run: 돌리기 위하여
### 1. 다음과 같이 디렉터리 구조를 구성하십시오
```
root/
├── build/
├── external/
├── resource/
├── src/
└── CMakelists.txt
```

- `resource/`는 제 취향입니다. 텍스쳐 파일을 한데 정리해서 넣기 위해 만들었습니다. 필요없다고 생각하면 하지맙시다.

### 2. 의존성을 추가하십시오
이 프로젝트는 다음 라이브러리에 의존성이 있습니다:
<div class="table-responsive">
  <table class="table table-bordered" style="border-radius: 5px;
    overflow: hidden;">
    <colgroup>
    <col style="width: 0.3vw;">
    <col style="width: 0.1vw;">
  </colgroup>
    <thead class="thead-light">
      <tr style="border-bottom: none;">
        <th scope="col">라이브러리 명</th>
        <th scope="col">디렉토리 명</th>
        <th scope="col">목적</th>
        <th scope="col">참조</th>
        <th scope="col">비고</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>{fmt}</td>
        <td>fmt/</td>
        <td>형식화된 텍스트 출력에 사용합니다.</td>
        <td><a href="https://github.com/fmtlib/fmt">Repository</a></td>
        <td></td>
      </tr>
      <tr>
        <td>GLAD</td>
        <td>glad/</td>
        <td>OS 플랫폼 독립적으로 OpenGL을 사용할 수 있도록 합니다. (더 편하게 OpenGL 개발을 할 수 있습니다. 😅)</td>
        <td><a href="https://glad.dav1d.de/">link</a></td>
        <td>gl 버전을 4.3 이상으로 설정한 후 generate 하십시오</td>
      </tr>
      <tr>
        <td>GLFW</td>
        <td>glfw/</td>
        <td>윈도우 생성, 입력 이벤트 리스닝 등을 위해 사용합니다.</td>
        <td><a href="https://github.com/glfw/glfw">Repository</a></td>
        <td></td>
      </tr>
      <tr>
        <td>GLM</td>
        <td>glm/</td>
        <td>벡터, 행렬 등의 객체 생성 및 계산에 사용합니다.</td>
        <td><a href="https://github.com/icaven/glm">Repository</a></td>
        <td></td>
      </tr>
      <tr>
        <td>stb</td>
        <td>stb/</td>
        <td>텍스쳐 출력을 위해 이미지를 파일시스템으로부터 읽어들일 때 사용합니다.</td>
        <td><a href="https://github.com/nothings/stb">Repository</td>
        <td></td>
      </tr>
    </tbody>
  </table>
</div>

`external/` 폴더 밑에 `git submodule add [git repo url] [directory name]`으로 glad를 제외한 모든 라이브러리에 대해 명령어를 수행합니다.

glad는 generate하여 내려 받은 파일을 압축 해제 하여 안의 내용물을 `glad/` 폴더를 만들어 하위에 집어넣습니다. 해당 절차가 끝나면 `glad/` 디렉터리의 구조는 다음과 같습니다.
```
glad/
├── include/
│   ├── glad/
│   │   └── glad.h
│   └── KHR/
│       └── khrplatform.h
└── src/
    └── glad.c
```

### 3. main.cpp를 추가하십시오
`root/src/` 디렉터리에 `main.cpp`를 추가합니다. 사용합니다.

### 4. 실행하기
앞서 모든 설정이 끝났다면 디렉터리 구조는 다음과 같아집니다.
```
root/
├── build/
├── external/
│   ├── fmt/
│   ├── glad/
│   ├── glfw/
│   ├── glm/
│   └── std/
├── resource/
├── src/
└── CMakelists.txt
```

1. 의존성 설정이 모두 끝난 경우에는 `root/bulid/` 폴더로 이동해서 `cmake -G Ninja ..` 명령어를 수행하여 빌드합니다.
1-1. 빌드 중 나타난 에러를 해결하거나 코드 변경 후 빌드를 하려면 `Ninja`를 수행합니다.
2. 성공적이라면 `build/` 디렉터리 밑에 `minig.exe` 파일이 생성됩니다. 실행해봅니다.

## FYI: 일러둠 
*WIP*

<style>
  .table thead th {
    border-bottom: none;
  }
  .table tbody tr:first-child td {
    border-top: none;
  }
</style>

<div class="table-responsive">
  <table class="table table-bordered" style="border-radius: 5px;
    overflow: hidden;">
    <colgroup>
    <col style="width: 0.3vw;">
  </colgroup>
    <thead class="thead-light">
      <tr style="border-bottom: none;">
        <th scope="col">namespace</th>
        <th scope="col">클래스</th>
        <th scope="col">목적</th>
        <th scope="col">사용</th>
        <th scope="col">추가 작업</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>minig</td>
        <td>ApplicationWindow</td>
        <td style="text-align: justify;">GLFW 래퍼 클래스. 윈도우를 생성하기 위한 GLFW 컨텍스트와 GLAD 라이브러리를 초기화합니다.</td>
        <td></td>
      </tr>
      <tr>
        <td>minig</td>
        <td>Graphical</td>
        <td>OpenGL를 사용한 어플리케이션의 메인 루프. </td>
      </tr>
      <tr>
        <td>minig</td>
        <td>EventHandler</td>
        <td>GLFW 입력 이벤트 콜백 래퍼 클래스. </td>
      </tr>
      <tr>
        <td>minig</td>
        <td>ShaderProgram</td>
        <td>OpenGL의 셰이더 컴파일 및 링크 과정에 대한 래핑. </td>
      </tr>
      <tr>
        <td>minig</td>
        <td>Colored</td>
        <td>내용 F</td>
      </tr>
      <tr>
        <td>minig</td>
        <td>Textured</td>
        <td>내용 F</td>
      </tr>
    </tbody>
  </table>
</div>