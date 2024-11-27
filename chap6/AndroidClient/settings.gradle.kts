pluginManagement {
    repositories {
        google()
        mavenCentral()
        gradlePluginPortal()
    }
}
dependencyResolutionManagement {
    repositoriesMode.set(RepositoriesMode.FAIL_ON_PROJECT_REPOS)
    repositories {
        google()
        mavenCentral()
        /**eclipse paho ของเดิม
         *         maven {
         *             url "https://repo.eclipse.org/content/repositories/paho-snapshots/"
         *         }
         */
        maven(url = "https://repo.eclipse.org/content/repositories/paho-snapshots/")
    }
}

rootProject.name = "Android Client"
include(":app")
