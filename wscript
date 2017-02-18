#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'kw'
VERSION = '2.0.0'

def resolve(ctx):

    ctx.add_dependency(
        name='waf-tools',
        recurse=True,
        optional=False,
        resolver='git',
        method='semver',
        major=3,
        sources=['github.com/steinwurf/waf-tools.git'])

    # Internal dependencies
    if ctx.is_toplevel():

        ctx.add_dependency(
            name='gtest',
            recurse=True,
            optional=False,
            resolver='git',
            method='semver',
            major=3,
            sources=['github.com/steinwurf/gtest.git'])


def configure(conf):
    print("kw configure")


def build(bld):
    print("kw build")

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_KW_VERSION="{}"'.format(VERSION))

    bld(includes='src',
        export_includes='src',
        name='kw_includes')

    if bld.is_toplevel():

        # Only build test when executed from the top-level wscript,
        # i.e. not when included as a dependency
        bld.recurse('test')
        bld.recurse('examples')
